/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

 use namespace HH\Lib\{Str, Vec};

/**
 * An <x:frag /> is a transparent wrapper around any number of elements. When
 * you render it just the children will be rendered. When you append it to an
 * element the <x:frag /> will disappear and each child will be sequentially
 * appended to the element.
 */
xhp class x:frag extends :x:primitive {
  protected async function stringifyAsync(): Awaitable<string> {
    return await Vec\map_async(
      $this->getChildren(),
      async $child ==> await :xhp::renderChildAsync($child),
    ) |> Str\join($$, '');
  }
}
