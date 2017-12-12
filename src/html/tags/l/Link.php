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

class :link extends :xhp:html-singleton {
  attribute
    Stringish as,
    enum {'anonymous', 'use-credentials'} crossorigin,
    Stringish href,
    Stringish hreflang,
    Stringish media,
    Stringish rel @required,
    Stringish sizes,
    Stringish type;
  category %metadata;
  protected string $tagName = 'link';
}
