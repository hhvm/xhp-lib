<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :area extends :xhp:html-singleton {
  attribute
    Stringish alt,
    Stringish coords,
    Stringish download,
    Stringish href,
    bool hreflang,
    Stringish media,
    Stringish rel,
    enum {
      'circ',
      'circle',
      'default',
      'poly',
      'polygon',
      'rect',
      'rectangle',
    } shape,
    Stringish target,
    Stringish type;
  category %flow, %phrase;
  protected string $tagName = 'area';
}
