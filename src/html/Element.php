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

/**
 * This is the base library of HTML elements for use in XHP. This includes all
 * non-deprecated tags and attributes. Elements in this file should stay as
 * close to spec as possible. Facebook-specific extensions should go into their
 * own elements.
 */
abstract class :xhp:html-element extends :x:primitive {

  attribute
    // Global HTML attributes
    Stringish accesskey,
    Stringish class,
    bool contenteditable,
    Stringish contextmenu,
    Stringish dir,
    bool draggable,
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

  public function getID(): string {
    return $this->requireUniqueID();
  }

  public function requireUniqueID(): string {
    $id = $this->:id;
    if ($id === null || $id === '') {
      $this->setAttribute('id', $id = substr(md5(mt_rand(0, 100000)), 0, 10));
    }
    return (string) $id;
  }

  protected final function renderBaseAttrs(): string {
    $buf = '<'.$this->tagName;
    foreach ($this->getAttributes() as $key => $val) {
      if ($val !== null && $val !== false) {
        if ($val === true) {
          $buf .= ' '.htmlspecialchars($key);
        } else {
          $buf .= ' '.htmlspecialchars($key).'="'.
            htmlspecialchars($val, ENT_COMPAT).'"';
        }
      }
    }
    return $buf;
  }

  public function addClass(string $class): this {
    $this->setAttribute(
      'class',
      trim($this->:class.' '.$class),
    );
    return $this;
  }

  public function conditionClass(bool $cond, string $class): this {
    if ($cond) {
      $this->addClass($class);
    }
    return $this;
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
