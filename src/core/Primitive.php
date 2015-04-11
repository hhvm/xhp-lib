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
    return $this->asyncToString()->getWaitHandle()->join();
  }

  final public async function asyncToString(): Awaitable<string> {
    await $this->__flushElementChildren();
    if (:xhp::$ENABLE_VALIDATION) {
      $this->validateChildren();
    }
    return $this->stringify();
  }
}
