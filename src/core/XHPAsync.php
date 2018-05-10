<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

trait XHPAsync implements XHPAwaitable {
  require extends :x:element;

  abstract protected function asyncRender(): Awaitable<XHPRoot>;

  final protected function render(): XHPRoot {
    throw new Exception(
      'You need to call asyncRender() on XHP elements that use XHPAwaitable',
    );
  }
}
