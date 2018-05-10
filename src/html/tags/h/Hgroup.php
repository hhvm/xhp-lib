<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :hgroup extends :xhp:html-element {
  category %flow, %heading;
  children (:h1 | :h2 | :h3 | :h4 | :h5 | :h6)+;
  protected string $tagName = 'hgroup';
}
