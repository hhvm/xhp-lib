<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :keygen extends :xhp:html-singleton {
  attribute
    bool autofocus,
    Stringish challenge,
    bool disabled,
    Stringish form,
    Stringish keytype,
    Stringish name;
  category %flow, %phrase, %interactive;
  protected string $tagName = 'keygen';
}
