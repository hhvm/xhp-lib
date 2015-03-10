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

class XHPAttributeRequiredException extends XHPException {
  public function __construct(:xhp $that, string $attr) {
    parent::__construct(
      'Required attribute `'.$attr.'` was not specified in element '.
      '`'.XHPException::getElementName($that)."`.\n\n".
      $that->source
    );
  }
}
