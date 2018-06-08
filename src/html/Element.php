<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

/**
 * This is the base library of HTML elements for use in XHP. This includes all
 * non-deprecated tags and attributes. Elements in this file should stay as
 * close to spec as possible. Facebook-specific extensions should go into their
 * own elements.
 */
abstract class :xhp:html-element extends :x:primitive {
  use XHPBaseHTMLHelpers;

  // enum { 'true', 'false' } attributes: these are actually tri-state -
  // the implied third value is usually 'auto' or 'inherit'; for example,
  // contenteditable defaults to 'inherit' if unspecified, so
  // contenteditable=false is valid ans has meaning

  attribute
    // Global HTML attributes
    Stringish accesskey,
    Stringish class,
    enum {'true', 'false'} contenteditable,
    Stringish contextmenu,
    Stringish dir,
    enum {'true', 'false'} draggable,
    Stringish dropzone,
    bool hidden,
    Stringish id,
    bool inert,
    Stringish itemid,
    Stringish itemprop,
    Stringish itemref,
    Stringish itemscope,
    Stringish itemtype,
    Stringish lang,
    Stringish role,
    enum {'true', 'false'} spellcheck,
    Stringish style,
    Stringish tabindex,
    Stringish title,
    enum {'yes', 'no'} translate,

    // Javascript events
    Stringish onabort,
    Stringish onblur,
    Stringish oncancel,
    Stringish oncanplay,
    Stringish oncanplaythrough,
    Stringish onchange,
    Stringish onclick,
    Stringish onclose,
    Stringish oncontextmenu,
    Stringish oncuechange,
    Stringish ondblclick,
    Stringish ondrag,
    Stringish ondragend,
    Stringish ondragenter,
    Stringish ondragexit,
    Stringish ondragleave,
    Stringish ondragover,
    Stringish ondragstart,
    Stringish ondrop,
    Stringish ondurationchange,
    Stringish onemptied,
    Stringish onended,
    Stringish onerror,
    Stringish onfocus,
    Stringish oninput,
    Stringish oninvalid,
    Stringish onkeydown,
    Stringish onkeypress,
    Stringish onkeyup,
    Stringish onload,
    Stringish onloadeddata,
    Stringish onloadedmetadata,
    Stringish onloadstart,
    Stringish onmousedown,
    Stringish onmouseenter,
    Stringish onmouseleave,
    Stringish onmousemove,
    Stringish onmouseout,
    Stringish onmouseover,
    Stringish onmouseup,
    Stringish onmousewheel,
    Stringish onpause,
    Stringish onplay,
    Stringish onplaying,
    Stringish onprogress,
    Stringish onratechange,
    Stringish onreset,
    Stringish onresize,
    Stringish onscroll,
    Stringish onseeked,
    Stringish onseeking,
    Stringish onselect,
    Stringish onshow,
    Stringish onstalled,
    Stringish onsubmit,
    Stringish onsuspend,
    Stringish ontimeupdate,
    Stringish ontoggle,
    Stringish onvolumechange,
    Stringish onwaiting;

  protected string $tagName = '';

  protected final function renderBaseAttrs(): string {
    $buf = '<'.$this->tagName;
    foreach ($this->getAttributes() as $key => $val) {
      if ($val !== null && $val !== false) {
        if ($val === true) {
          $buf .= ' '.htmlspecialchars($key);
        } else {
          if ($val instanceof XHPUnsafeAttributeValue) {
            $val_str = $val->toHTMLString();
          } else {
            $val_str = htmlspecialchars($val, ENT_COMPAT);
          }

          $buf .= ' '.
            htmlspecialchars($key).
            '="'.
            $val_str.
            '"';
        }
      }
    }
    return $buf;
  }

  protected function stringify(): string {
    $buf = $this->renderBaseAttrs().'>';
    foreach ($this->getChildren() as $child) {
      $buf .= :xhp::renderChild($child);
    }
    $buf .= '</'.$this->tagName.'>';
    return $buf;
  }
}
