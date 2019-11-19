<?hh // strict
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
abstract class :x:element extends :x:composable-element implements XHPRoot {
  abstract protected function render(): XHPRoot;

  final public function toString(): string {
    return \HH\Asio\join($this->asyncToString());
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
    if (:xhp::isChildValidationEnabled()) {
      $this->validateChildren();
    }

    $self = $this;
    if ($self is XHPAwaitable) {
      $composed = /* HH_FIXME[4112] protected */await $self->asyncRender();
    } else {
      $composed = $this->render();
    }

    $composed->__transferContext($this->getAllContexts());
    if ($this is XHPHasTransferAttributes) {
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
