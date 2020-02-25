<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

xhp class option extends :xhp:pcdata_element {
  attribute
    bool disabled,
    string label,
    bool selected,
    string value;
  protected string $tagName = 'option';
}
