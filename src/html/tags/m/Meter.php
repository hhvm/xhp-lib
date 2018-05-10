<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :meter extends :xhp:html-element {
  attribute
    float high,
    float low,
    float max,
    float min,
    float optimum,
    float value;
  category %flow, %phrase;
  // Should not contain :meter
  children (pcdata | %phrase)*;
  protected string $tagName = 'meter';
}
