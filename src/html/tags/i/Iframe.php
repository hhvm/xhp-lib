<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :iframe extends :xhp:pcdata-element {
  attribute
    bool allowfullscreen,
    Stringish name,
    int height,
    Stringish sandbox,
    bool seamless,
    Stringish src,
    Stringish srcdoc,
    int width;
  category %flow, %phrase, %embedded, %interactive;
  protected string $tagName = 'iframe';
}
