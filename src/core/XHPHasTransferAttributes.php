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
 * Indicates that any attributes set on an element should be transferred to the
 * element returned from ::render() or ::asyncRender(). This is automatically
 * invoked by :x:element.
 */
interface XHPHasTransferAttributes {
  require extends :x:element;
  public function transferAttributesToRenderedRoot(
    :x:composable_element $root,
  ): void;
}
