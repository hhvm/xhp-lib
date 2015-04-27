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

interface HasXHPBaseHTMLHelpers {
  require extends :x:composable-element;

  public function addClass(string $class): this;
  public function conditionClass(bool $cond, string $class): this;
  public function requireUniqueID(): string;
  public function getID(): string;
}
