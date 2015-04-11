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

class :iframe extends :xhp:pcdata-element {
  attribute
    bool allowfullscreen, string name, int height, string sandbox,
    bool seamless, string src, string srcdoc, int width;
  category %flow, %phrase, %embedded, %interactive;
  protected string $tagName = 'iframe';
}
