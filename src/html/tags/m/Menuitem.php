<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
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
