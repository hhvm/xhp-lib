/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

use namespace Facebook\XHP\Core as x;

/**
 * These attributes may exist in all elements in an HTML document,
 * even if they are not an HTML element.
 * Source: https://html.spec.whatwg.org/#global-attributes
 */
trait GlobalAttributes {

  // enum { 'true', 'false' } attributes: these are actually tri-state -
  // the implied third value is usually 'auto' or 'inherit'; for example,
  // contenteditable defaults to 'inherit' if unspecified, so
  // contenteditable=false is valid ans has meaning

  attribute
    // Global attributes per spec
    string accesskey,
    enum {
      'off', // identical to none
      'none',
      'on', // identical to sentences
      'sentences',
      'words',
      'characters',
    } autocapitalize,
    bool autofocus,
    enum {'true', 'false'} contenteditable,
    enum {'auto', 'ltr', 'rtl'} dir,
    enum {'true', 'false'} draggable,
    string dropzone,
    enum {
      'enter',
      'done',
      'go',
      'next',
      'previous',
      'search',
      'send',
    } enterkeyhint,
    bool hidden,
    string is, // needs to be a name of a defined custom element
    enum {
      'decimal',
      'email',
      'full-width-latin',
      'kana',
      'katakana',
      'latin',
      'latin-name',
      'latin-prose',
      'none',
      'numeric',
      'search',
      'tel',
      'text',
      'url',
      'verbatim',
    } inputmode,
    string itemid,
    string itemprop,
    string itemref,
    string itemscope,
    string itemtype,
    string lang,
    string nonce,
    enum {'true', 'false'} spellcheck,
    string style,
    string tabindex,
    string title,
    enum {'yes', 'no'} translate;
}
