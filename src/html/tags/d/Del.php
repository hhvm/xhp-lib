<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :del extends :xhp:html-element {
  attribute
    string cite,
    string datetime;
  category %flow, %phrase;
  // transparent
  children (pcdata | %flow)*;
  protected string $tagName = 'del';
}
