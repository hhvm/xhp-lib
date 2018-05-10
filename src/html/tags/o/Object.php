<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :object extends :xhp:html-element {
  attribute
    Stringish data,
    int height,
    Stringish form,
    Stringish name,
    Stringish type,
    bool typemustmatch,
    Stringish usemap,
    int width;
  category %flow, %phrase, %embedded, %interactive;
  children (:param*, (pcdata | %flow)*);
  protected string $tagName = 'object';
}
