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
use namespace HH\Lib\{Str, Vec};

/**
 * This is the base library of HTML elements for use in XHP. This includes all
 * non-deprecated tags and attributes. Elements in this file should stay as
 * close to spec as possible. Facebook-specific extensions should go into their
 * own elements.
 */
abstract xhp class element extends x\primitive {
  use XHPHTMLHelpers;

  // enum { 'true', 'false' } attributes: these are actually tri-state -
  // the implied third value is usually 'auto' or 'inherit'; for example,
  // contenteditable defaults to 'inherit' if unspecified, so
  // contenteditable=false is valid ans has meaning

  attribute
    // Global HTML attributes
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
    string class,
    enum {'true', 'false'} contenteditable,
    string contextmenu,
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
    string id,
    string is, // needs to be a name of a defined custom element
    bool inert,
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
    string role,
    enum {'true', 'false'} spellcheck,
    string style,
    string tabindex,
    string title,
    enum {'yes', 'no'} translate,

    // Javascript events
    string onabort,
    string onauxclick,
    string onblur,
    string oncancel,
    string oncanplay,
    string oncanplaythrough,
    string onchange,
    string onclick,
    string onclose,
    string oncontextmenu,
    string oncopy,
    string oncuechange,
    string oncut,
    string ondblclick,
    string ondrag,
    string ondragend,
    string ondragenter,
    string ondragexit,
    string ondragleave,
    string ondragover,
    string ondragstart,
    string ondrop,
    string ondurationchange,
    string onemptied,
    string onended,
    string onerror,
    string onfocus,
    string onformdata,
    string oninput,
    string oninvalid,
    string onkeydown,
    string onkeypress,
    string onkeyup,
    string onload,
    string onloadeddata,
    string onloadedmetadata,
    string onloadstart,
    string onmousedown,
    string onmouseenter,
    string onmouseleave,
    string onmousemove,
    string onmouseout,
    string onmouseover,
    string onmouseup,
    string onmousewheel,
    string onpaste,
    string onpause,
    string onplay,
    string onplaying,
    string onprogress,
    string onratechange,
    string onreset,
    string onresize,
    string onscroll,
    string onsecuritypolicyviolation,
    string onseeked,
    string onseeking,
    string onselect,
    string onshow,
    string onslotchange,
    string onstalled,
    string onsubmit,
    string onsuspend,
    string ontimeupdate,
    string ontoggle,
    string onvolumechange,
    string onwaiting,
    string onwheel;

  protected string $tagName = '';

  protected final function renderBaseAttrs(): string {
    $buf = '<'.$this->tagName;
    foreach ($this->getAttributes() as $key => $val) {
      if ($val !== null && $val !== false) {
        if ($val === true) {
          $buf .= ' '.\htmlspecialchars($key);
        } else {
          if ($val is \Facebook\XHP\UnsafeAttributeValue) {
            $val_str = $val->toHTMLString();
          } else {
            $val_str = \htmlspecialchars((string)$val, \ENT_COMPAT);
          }

          $buf .= ' '.\htmlspecialchars($key).'="'.$val_str.'"';
        }
      }
    }
    return $buf;
  }

  <<__Override>>
  protected async function stringifyAsync(): Awaitable<string> {
    $buf = $this->renderBaseAttrs().'>';
    $buf .= await Vec\map_async(
      $this->getChildren(),
      async $child ==> await self::renderChildAsync($child),
    )
      |> Str\join($$, '');
    $buf .= '</'.$this->tagName.'>';
    return $buf;
  }
}
