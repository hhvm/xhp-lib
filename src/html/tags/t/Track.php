<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

xhp class track extends :xhp:html_singleton {
  attribute
    bool default,
    enum {'subtitles', 'captions', 'descriptions', 'chapters', 'metadata'} kind,
    string label,
    string src,
    string srclang;
  protected string $tagName = 'track';
}
