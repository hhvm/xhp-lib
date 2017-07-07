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
