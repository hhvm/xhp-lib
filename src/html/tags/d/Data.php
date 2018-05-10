<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :data extends :xhp:html-element {
  attribute Stringish value @required;
  category %flow, %phrase;
  children (%phrase*);
  protected string $tagName = 'data';
}
