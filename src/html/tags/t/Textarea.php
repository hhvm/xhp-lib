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

class :textarea extends :xhp:pcdata-element {
  attribute
    enum {'on', 'off'} autocomplete, bool autofocus, int cols, string dirname,
    bool disabled, string form, int maxlength, int minlength, string name,
    string placeholder, bool readonly, bool required, int rows,
    enum {'soft', 'hard'} wrap;
  category %flow, %phrase, %interactive;
  protected string $tagName = 'textarea';
}
