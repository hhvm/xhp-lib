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

class :script extends :xhp:raw-pcdata-element {
  attribute bool async, Stringish charset,
  enum {'anonymous', 'use-credentials'} crossorigin, bool defer, Stringish src,
  Stringish type,
  // Legacy
  Stringish language;
  category %flow, %phrase, %metadata;
  protected string $tagName = 'script';
}
