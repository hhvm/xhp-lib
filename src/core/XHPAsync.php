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

trait XHPAsync {

  require extends :x:element;
  require implements XHPAwaitable;

  abstract protected function asyncRender(): Awaitable<XHPRoot>;

  final protected function render(): XHPRoot {
    throw new Exception(
      'You need to call asyncRender() on XHP elements that use XHPAwaitable',
    );
  }
}
