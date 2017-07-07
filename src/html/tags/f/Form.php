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

class :form extends :xhp:html-element {
  attribute
    Stringish action,
    Stringish accept-charset,
    enum {'on', 'off'} autocomplete,
    Stringish enctype,
    enum {'get', 'post'} method,
    Stringish name,
    bool novalidate,
    Stringish target;
  category %flow;
  // Should not contain :form
  children (pcdata | %flow)*;
  protected string $tagName = 'form';
}
