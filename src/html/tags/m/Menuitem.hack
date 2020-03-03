/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

xhp class menuitem extends :xhp:html_singleton {
  attribute
    bool checked,
    string command,
    bool default,
    bool disabled,
    string label,
    string icon,
    string radiogroup,
    enum {'checkbox', 'command', 'radio'} type;
  protected string $tagName = 'menuitem';
}
