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

class :button extends :xhp:html-element {
  attribute
    bool autofocus,
    bool disabled,
    Stringish form,
    Stringish formaction,
    Stringish formenctype,
    enum {'get', 'post'} formmethod,
    bool formnovalidate,
    Stringish formtarget,
    Stringish menu,
    Stringish name,
    enum {'submit', 'button', 'reset'} type,
    Stringish value;
  category %flow, %phrase, %interactive;
  // Should not contain interactive
  children (pcdata | %phrase)*;
  protected string $tagName = 'button';
}
