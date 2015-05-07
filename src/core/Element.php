<?hh // strict
/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/**
 * :x:element defines an interface that all user-land elements should subclass
 * from. The main difference between :x:element and :x:primitive is that
 * subclasses of :x:element should implement `render()` instead of `stringify`.
 * This is important because most elements should not be dealing with strings
 * of markup.
 */
abstract class :x:element extends :x:composable-element implements XHPRoot {
  abstract protected function render(): XHPRoot;

  final public function toString(): string {
    return $this->asyncToString()->getWaitHandle()->join();
  }

  final public async function asyncToString(): Awaitable<string> {
    $that = await $this->__flushRenderedRootElement();
    $ret = await $that->asyncToString();
    return $ret;
  }

  final protected async function __flushSubtree(): Awaitable<:x:primitive> {
    $that = await $this->__flushRenderedRootElement();
    return await $that->__flushSubtree();
  }

  protected async function __renderAndProcess(): Awaitable<XHPRoot> {
    if (:xhp::$ENABLE_VALIDATION) {
      $this->validateChildren();
    }

    if ($this instanceof XHPAwaitable) {
      // UNSAFE - interfaces don't support 'protected': facebook/hhvm#4830
      $composed = await $this->asyncRender();
    } else {
      $composed = $this->render();
    }

    $composed->__transferContext($this->getAllContexts());
    if ($this instanceof XHPHasTransferAttributes) {
      $this->transferAttributesToRenderedRoot($composed);
    }

    return $composed;
  }

  final protected async function __flushRenderedRootElement(
  ): Awaitable<:x:primitive> {
    $that = $this;
    // Flush root elements returned from render() to an :x:primitive
    while ($that instanceof :x:element) {
      $that = await $that->__renderAndProcess();
    }

    if ($that instanceof :x:primitive) {
      return $that;
    }

    // render() must always (eventually) return :x:primitive
    throw new XHPCoreRenderException($this, $that);
  }
}
