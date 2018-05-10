<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :datalist extends :xhp:html-element {
  category %flow, %phrase;
  children (%phrase+ | :option*);
  protected string $tagName = 'datalist';
}
