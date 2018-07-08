<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :script extends :xhp:raw-pcdata-element {
  attribute
    bool async,
    Stringish charset,
    enum {'anonymous', 'use-credentials'} crossorigin,
    bool defer,
    Stringish src,
    Stringish type,
    Stringish integrity,
    // Legacy
    Stringish language;
  category %flow, %phrase, %metadata;
  protected string $tagName = 'script';
}
