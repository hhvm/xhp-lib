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

class XHPInvalidChildrenException extends XHPException {
  public function __construct(:x:composable-element $that, int $index) {
    parent::__construct(
      'Element `'.XHPException::getElementName($that).'` was rendered with '.
      "invalid children.\n\n".
      "$that->source\n\n".
      "Verified $index children before failing.\n\n".
      "Children expected:\n".$that->__getChildrenDeclaration()."\n\n".
      "Children received:\n".$that->__getChildrenDescription()
    );
  }
}
