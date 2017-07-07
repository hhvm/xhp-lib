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

class :menuitem extends :xhp:html-singleton {
  attribute
    bool checked,
    Stringish command,
    bool default,
    bool disabled,
    Stringish label,
    Stringish icon,
    Stringish radiogroup,
    enum {'checkbox', 'command', 'radio'} type;
  protected string $tagName = 'menuitem';
}
