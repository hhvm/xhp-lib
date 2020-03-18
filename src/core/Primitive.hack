/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\Elements\Core;

use namespace HH\Lib\Dict;

/**
 * :x:primitive lays down the foundation for very low-level elements. You
 * should directly :x:primitive only if you are creating a core element that
 * needs to directly implement stringify(). All other elements should subclass
 * from :x:element.
 */
abstract xhp class primitive extends node {
  abstract protected function stringifyAsync(): Awaitable<string>;

  final public async function toStringAsync(): Awaitable<string> {
    $that = await $this->__flushSubtree();
    return await $that->stringifyAsync();
  }

  final private async function __flushElementChildren(): Awaitable<void> {
    $children = $this->getChildren();
    $awaitables = dict[];
    foreach ($children as $idx => $child) {
      if ($child is node) {
        $child->__transferContext($this->getAllContexts());
        $awaitables[$idx] = $child->__flushSubtree();
      }
    }
    if ($awaitables) {
      $awaited = await Dict\from_async($awaitables);
      foreach ($awaited as $idx => $child) {
        $children[$idx] = $child;
      }
    }
    $this->replaceChildren($children);
  }

  final protected async function __flushSubtree(): Awaitable<primitive> {
    await $this->__flushElementChildren();
    if (xhp::isChildValidationEnabled()) {
      $this->validateChildren();
    }
    return $this;
  }
}
