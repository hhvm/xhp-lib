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

class :ol extends :xhp:html-element {
  attribute
    bool reversed,
    int start,
    enum {'1', 'a', 'A', 'i', 'I'} type;
  category %flow;
  children (:li)*;
  protected string $tagName = 'ol';
}
