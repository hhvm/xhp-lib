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

class :area extends :xhp:html-singleton {
  attribute
    string alt, string coords, string download, string href, bool hreflang,
    string media, string rel,
    enum {
      'circ', 'circle', 'default', 'poly', 'polygon', 'rect', 'rectangle'
    } shape, string target, string type;
  category %flow, %phrase;
  protected string $tagName = 'area';
}
