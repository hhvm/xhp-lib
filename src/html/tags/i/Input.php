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
    Stringish accept, Stringish alt, enum {'on', 'off'} autocomplete, bool autofocus,
    bool checked, Stringish dirname, bool disabled, Stringish form,
    Stringish formaction, Stringish formenctype, enum {'get', 'post'} formmethod,
    bool formnovalidate, Stringish formtarget, int height, enum {
      'email', 'full-width-latin', 'kana', 'katakana', 'latin', 'latin-name',
      'latin-prose', 'numeric', 'tel', 'url', 'verbatim'
    } inputmode, Stringish list, float max, int maxlength, float min,
    int minlength, bool multiple, Stringish name, Stringish pattern,
    Stringish placeholder, bool readonly, bool required, int size, Stringish src,
    float step, enum {
      'hidden', 'text', 'search', 'tel', 'url', 'email', 'password',
      'datetime', 'date', 'month', 'week', 'time', 'datetime-local', 'number',
      'range', 'color', 'checkbox', 'radio', 'file', 'submit', 'image',
      'reset', 'button'
    } type, Stringish value, int width;
  category %flow, %phrase, %interactive;
  protected string $tagName = 'input';
}
