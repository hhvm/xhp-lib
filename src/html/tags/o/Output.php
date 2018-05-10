<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :output extends :xhp:html-element {
  attribute
    Stringish for,
    Stringish form,
    Stringish name;
  category %flow, %phrase;
  children (pcdata | %phrase)*;
  protected string $tagName = 'output';
}
