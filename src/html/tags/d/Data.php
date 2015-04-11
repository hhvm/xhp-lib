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

class :data extends :xhp:html-element {
  attribute string value @required;
  category %flow, %phrase;
  children (%phrase*);
  protected string $tagName = 'data';
}
