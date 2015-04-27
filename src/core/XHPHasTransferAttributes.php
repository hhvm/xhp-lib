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
 * Indicates that any attributes set on an element should be transferred to the
 * element returned from ::render() or ::asyncRender(). This is automatically
 * invoked by :x:element.
 */
interface XHPHasTransferAttributes {
  require extends :x:element;
  public function transferAttributesToRenderedRoot(
    :x:composable-element $root,
  ): void;
}
