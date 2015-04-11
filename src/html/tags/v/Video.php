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

class :video extends :xhp:html-element {
  attribute
    bool autoplay, bool controls,
    enum {'anonymous', 'use-credentials'} crossorigin, int height, bool loop,
    string mediagroup, bool muted, string poster,
    enum {'none', 'metadata', 'auto'} preload, string src, int width;
  category %flow, %phrase, %embedded, %interactive;
  children (:source*, :track*, (pcdata | %flow)*);
  protected string $tagName = 'video';
}
