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
 * INCREDIBLY AWESOME: Specify an element as awaitable on render.
 *
 * This allows you to use await inside your XHP objects. For instance, you could
 * fetch data inside your XHP elements using await and the calls to the DB would
 * be batched together when the element is rendered.
 */
interface XHPAwaitable {
  require extends :x:element;
  protected function asyncRender(): Awaitable<XHPRoot>;
}
