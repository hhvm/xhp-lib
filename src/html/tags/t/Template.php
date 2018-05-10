<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :template extends :xhp:html-element {
  category %flow, %phrase, %metadata;
  // The children declaration for this element is extraordinarily verbose so
  // I leave it to you to use it appropriately.
  protected string $tagName = 'template';
}
