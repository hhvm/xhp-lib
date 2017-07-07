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
