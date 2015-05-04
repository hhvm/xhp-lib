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
    if (:xhp::$ENABLE_VALIDATION) {
      $this->validateChildren();
    }
    $that = await $this->__flushRenderedRootElement();
    $ret = await $that->asyncToString();
    return $ret;
  }

  final protected async function __flushRenderedRootElement(
  ): Awaitable<:x:primitive> {
    $that = $this;
    // Flush root elements returned from render() to an :x:primitive
    do {
      if (:xhp::$ENABLE_VALIDATION) {
        $that->validateChildren();
      }
      if ($that instanceof XHPAwaitable) {
        $composed = await static::__xhpAsyncRender($that);
      } else {
        invariant(
          $that instanceof :x:element,
          "Trying to render something that isn't an element",
        );
        $composed = $that->render();
      }
      invariant(
        $composed instanceof :x:composable-element,
        'Did not get an :x:element from render()',
      );
      $composed->__transferContext($that->getAllContexts());
      if ($that instanceof XHPHasTransferAttributes) {
        $that->transferAttributesToRenderedRoot($composed);
      }
      $that = $composed;
    } while ($composed instanceof :x:element);

    if (!($composed instanceof :x:primitive)) {
      // render() must always (eventually) return :x:primitive
      throw new XHPCoreRenderException($this, $that);
    }

    return $composed;
  }
}
