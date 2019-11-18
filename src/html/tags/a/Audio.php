<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :audio extends :xhp:html-element {
  attribute
    bool autoplay,
    bool controls,
    enum {'anonymous', 'use-credentials'} crossorigin,
    bool loop,
    string mediagroup,
    bool muted,
    enum {'none', 'metadata', 'auto'} preload,
    string src;
  category %flow, %phrase, %embedded, %interactive;
  children (:source*, :track*, (pcdata | %flow)*);
  protected string $tagName = 'audio';
}
