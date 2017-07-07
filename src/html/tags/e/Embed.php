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
