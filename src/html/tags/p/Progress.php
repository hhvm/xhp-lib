<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :progress extends :xhp:html-element {
  attribute
    float max,
    float value;
  category %flow, %phrase;
  // Should not contain :progress
  children (pcdata | %phrase)*;
  protected string $tagName = 'progress';
}
