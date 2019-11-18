<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :select extends :xhp:html-element {
  attribute
    bool autofocus,
    bool disabled,
    string form,
    bool multiple,
    string name,
    bool required,
    int size;
  category %flow, %phrase, %interactive;
  children (:option | :optgroup)*;
  protected string $tagName = 'select';
}
