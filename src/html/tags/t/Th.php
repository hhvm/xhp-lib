<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :th extends :xhp:html-element {
  attribute
    Stringish abbr,
    int colspan,
    Stringish headers,
    int rowspan,
    enum {'col', 'colgroup', 'row', 'rowgroup'} scope,
    Stringish sorted;
  children (pcdata | %flow)*;
  protected string $tagName = 'th';
}
