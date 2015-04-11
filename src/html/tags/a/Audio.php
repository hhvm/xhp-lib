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

class :audio extends :xhp:html-element {
  attribute
    bool autoplay, bool controls,
    enum {'anonymous', 'use-credentials'} crossorigin, bool loop,
    string mediagroup, bool muted, enum {'none', 'metadata', 'auto'} preload,
    string src;
  category %flow, %phrase, %embedded, %interactive;
  children (:source*, :track*, (pcdata | %flow)*);
  protected string $tagName = 'audio';
}
