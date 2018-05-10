<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :h2 extends :xhp:html-element {
  category %flow;
  children (pcdata | %phrase)*;
  protected string $tagName = 'h2';
}
