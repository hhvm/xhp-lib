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

class :address extends :xhp:html-element {
  category %flow;
  // May not contain %heading, %sectioning, :header, :footer, or :address
  children (pcdata | %flow)*;
  protected string $tagName = 'address';
}
