<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :td extends :xhp:html-element {
  attribute
    int colspan,
    string headers,
    int rowspan;
  children (pcdata | %flow)*;
  protected string $tagName = 'td';
}
