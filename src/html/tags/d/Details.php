<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :details extends :xhp:html-element {
  attribute bool open;
  category %flow, %phrase, %interactive;
  children (:summary, %flow+);
  protected string $tagName = 'details';
}
