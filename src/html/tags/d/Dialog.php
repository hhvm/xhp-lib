<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :dialog extends :xhp:html-element {
  attribute bool open;
  category %flow, %sectioning;
  children (%flow);
  protected string $tagName = 'dialog';
}
