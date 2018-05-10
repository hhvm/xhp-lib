<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :menu extends :xhp:html-element {
  attribute
    Stringish label,
    enum {'popup', 'toolbar'} type;
  category %flow;
  children ((:menuitem | :hr | :menu)* | :li* | %flow*);
  protected string $tagName = 'menu';
}
