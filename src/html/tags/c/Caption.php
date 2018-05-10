<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :caption extends :xhp:html-element {
  // Should not contain :table
  children (pcdata | %flow)*;
  protected string $tagName = 'caption';
}
