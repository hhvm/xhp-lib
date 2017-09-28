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
 * :x:primitive lays down the foundation for very low-level elements. You
 * should directly :x:primitive only if you are creating a core element that
 * needs to directly implement stringify(). All other elements should subclass
 * from :x:element.
 */
abstract class :x:primitive extends :x:composable-element implements XHPRoot {
  abstract protected function stringify(): string;

  final public function toString(): string {
    return \HH\Asio\join($this->asyncToString());
  }

  final public async function asyncToString(): Awaitable<string> {
    $that = await $this->__flushSubtree();
    return $that->stringify();
  }

  final private async function __flushElementChildren(): Awaitable<void> {
    $children = $this->getChildren();
    $awaitables = Map {};
    foreach ($children as $idx => $child) {
      if ($child instanceof :x:composable-element) {
        $child->__transferContext($this->getAllContexts());
        $awaitables[$idx] = $child->__flushSubtree();
      }
    }
    if ($awaitables) {
      $awaited = await HH\Asio\m($awaitables);
      foreach ($awaited as $idx => $child) {
        $children[$idx] = $child;
      }
    }
    $this->replaceChildren($children);
  }

  final protected async function __flushSubtree(): Awaitable<:x:primitive> {
    await $this->__flushElementChildren();
    if (:xhp::isChildValidationEnabled()) {
      $this->validateChildren();
    }
    return $this;
  }
}
