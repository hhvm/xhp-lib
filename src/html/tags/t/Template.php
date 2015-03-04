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

class :template extends :xhp:html-element {
  category %flow, %phrase, %metadata;
  // The children declaration for this element is extraordinarily verbose so
  // I leave it to you to use it appropriately.
  protected string $tagName = 'template';
}
