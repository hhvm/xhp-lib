<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :img extends :xhp:html-singleton {
  attribute
    Stringish alt,
    enum {'anonymous', 'use-credentials'} crossorigin,
    int height,
    bool ismap,
    Stringish sizes,
    Stringish src,
    Stringish srcset,
    Stringish usemap,
    int width;
  category %flow, %phrase;
  protected string $tagName = 'img';
}
