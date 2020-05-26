/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\Core;

/**
 * element defines an interface that all user-land elements should subclass
 * from. The main difference between element and primitive is that
 * subclasses of element should implement `render()` instead of `stringify`.
 * This is important because most elements should not be dealing with strings
 * of markup.
 */
abstract xhp class element extends node {
  abstract protected function renderAsync(): Awaitable<node>;

  final public async function toStringAsync(): Awaitable<string> {
    $that = await $this->__flushRenderedRootElement();
    $ret = await $that->toStringAsync();
    return $ret;
  }

  final protected async function __flushSubtree(): Awaitable<primitive> {
    $that = await $this->__flushRenderedRootElement();
    return await $that->__flushSubtree();
  }

  protected async function __renderAndProcess(): Awaitable<node> {
    invariant(!$this->__isRendered, "Attempted to render XHP element twice");
    $this->__isRendered = true;
    if (\Facebook\XHP\ChildValidation\is_enabled()) {
      $this->validateChildren();
    }

    $composed = await $this->renderAsync();

    $composed->__transferContext($this->getAllContexts());
    if ($this is \HasXHPAttributeClobbering_DEPRECATED) {
      $this->transferAttributesToRenderedRoot($composed);
    }

    return $composed;
  }

  final protected async function __flushRenderedRootElement(
  ): Awaitable<primitive> {
    $that = $this;
    // Flush root elements returned from render() to an primitive
    while ($that is element) {
      $that = await $that->__renderAndProcess();
    }

    if ($that is primitive) {
      return $that;
    }

    // render() must always (eventually) return primitive
    throw new \Facebook\XHP\CoreRenderException($this, $that);
  }
}
