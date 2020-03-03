/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

/**
 * :x:element defines an interface that all user-land elements should subclass
 * from. The main difference between :x:element and :x:primitive is that
 * subclasses of :x:element should implement `render()` instead of `stringify`.
 * This is important because most elements should not be dealing with strings
 * of markup.
 */
abstract xhp class x:element extends :x:composable_element implements XHPRoot {
  abstract protected function renderAsync(): Awaitable<XHPRoot>;

  final public async function toStringAsync(): Awaitable<string> {
    $that = await $this->__flushRenderedRootElement();
    $ret = await $that->toStringAsync();
    return $ret;
  }

  final protected async function __flushSubtree(): Awaitable<:x:primitive> {
    $that = await $this->__flushRenderedRootElement();
    return await $that->__flushSubtree();
  }

  protected async function __renderAndProcess(): Awaitable<XHPRoot> {
    invariant(!$this->__isRendered, "Attempted to render XHP element twice");
    $this->__isRendered = true;
    if (:xhp::isChildValidationEnabled()) {
      $this->validateChildren();
    }

    $composed = await $this->renderAsync();

    $composed->__transferContext($this->getAllContexts());
    if ($this is HasXHPAttributeClobbering_DEPRECATED) {
      $this->transferAttributesToRenderedRoot($composed);
    }

    return $composed;
  }

  final protected async function __flushRenderedRootElement(
  ): Awaitable<:x:primitive> {
    $that = $this;
    // Flush root elements returned from render() to an :x:primitive
    while ($that is :x:element) {
      $that = await $that->__renderAndProcess();
    }

    if ($that is :x:primitive) {
      return $that;
    }

    // render() must always (eventually) return :x:primitive
    throw new XHPCoreRenderException($this, $that);
  }
}
