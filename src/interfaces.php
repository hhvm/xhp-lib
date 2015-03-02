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

interface XHPRoot extends XHPChild {
}

/**
 * INCREDIBLY DANGEROUS: Marks an object as a valid child of *any* element,
 * ignoring any child rules.
 *
 * This is useful when migrating to XHP as it allows you to embed non-XHP
 * content, usually in combination with XHPUnsafeRenderable; see MIGRATING.md
 * for more information.
 */
interface XHPAlwaysValidChild {
}

/**
 * INCREDIBLY DANGEROUS: Marks an object as being able to provide an HTML
 * string.
 *
 * This is useful when migrating to XHP as it allows you to embed non-XHP
 * content, usually in combination with XHPAlwaysValidChild; see MIGRATING.md
 * for more information.
 */
interface XHPUnsafeRenderable extends XHPChild {
  public function toHTMLString(): string;
}

/**
 * INCREDIBLY AWESOME: Specify an element as awaitable on render.
 *
 * This allows you to use await inside your XHP objects. For instance, you could
 * fetch data inside your XHP elements using await and the calls to the DB would
 * be batched together when the element is rendered.
 */
interface XHPAwaitable {
  require extends :x:element;
  // protected function asyncRender(): Awaitable<XHPRoot>
}
