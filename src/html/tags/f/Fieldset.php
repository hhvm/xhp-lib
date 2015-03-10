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

class :fieldset extends :xhp:html-element {
  attribute bool disabled, string form, string name;
  category %flow;
  children (:legend?, (pcdata | %flow)*);
  protected string $tagName = 'fieldset';
}
