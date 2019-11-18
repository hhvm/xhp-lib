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
    string data,
    int height,
    string form,
    string name,
    string type,
    bool typemustmatch,
    string usemap,
    int width;
  category %flow, %phrase, %embedded, %interactive;
  children (:param*, (pcdata | %flow)*);
  protected string $tagName = 'object';
}
