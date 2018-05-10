<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :embed extends :xhp:html-element {
  attribute
    int height,
    Stringish src,
    Stringish type,
    int width,
    /**
     * The following attributes are Flash specific.
     * Most notable use: youtube video embedding
     */
    bool allowfullscreen,
    enum {'always', 'never'} allowscriptaccess,
    Stringish wmode;

  category %flow, %phrase, %embedded, %interactive;
  children (pcdata | %phrase)*;
  protected string $tagName = 'embed';
}
