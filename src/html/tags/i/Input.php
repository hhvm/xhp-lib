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

class :input extends :xhp:html-singleton {
  attribute
    string accept, string alt, enum {'on', 'off'} autocomplete, bool autofocus,
    bool checked, string dirname, bool disabled, string form,
    string formaction, string formenctype, enum {'get', 'post'} formmethod,
    bool formnovalidate, string formtarget, int height, enum {
      'email', 'full-width-latin', 'kana', 'katakana', 'latin', 'latin-name',
      'latin-prose', 'numeric', 'tel', 'url', 'verbatim'
    } inputmode, string list, float max, int maxlength, float min,
    int minlength, bool multiple, string name, string pattern,
    string placeholder, bool readonly, bool required, int size, string src,
    float step, enum {
      'hidden', 'text', 'search', 'tel', 'url', 'email', 'password',
      'datetime', 'date', 'month', 'week', 'time', 'datetime-local', 'number',
      'range', 'color', 'checkbox', 'radio', 'file', 'submit', 'image',
      'reset', 'button'
    } type, string value, int width;
  category %flow, %phrase, %interactive;
  protected string $tagName = 'input';
}
