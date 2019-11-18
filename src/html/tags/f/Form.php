<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :form extends :xhp:html-element {
  attribute
    string action,
    string accept-charset,
    enum {'on', 'off'} autocomplete,
    string enctype,
    enum {'get', 'post'} method,
    string name,
    bool novalidate,
    string target;
  category %flow;
  // Should not contain :form
  children (pcdata | %flow)*;
  protected string $tagName = 'form';
}
