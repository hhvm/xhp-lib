<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

xhp class script extends :xhp:raw_pcdata_element {
  attribute
    bool async,
    string charset,
    enum {'anonymous', 'use-credentials'} crossorigin,
    bool defer,
    string src,
    string type,
    string integrity,
    // Legacy
    string language;
  category %flow, %phrase, %metadata;
  protected string $tagName = 'script';
}
