<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :q extends :xhp:html-element {
  attribute Stringish cite;
  category %flow, %phrase;
  children (pcdata | %phrase)*;
  protected string $tagName = 'q';
}
