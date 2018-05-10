<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class XHPAttributeRequiredException extends XHPException {
  public function __construct(:xhp $that, string $attr) {
    parent::__construct(
      'Required attribute `'.
      $attr.
      '` was not specified in element '.
      '`'.
      XHPException::getElementName($that).
      "`.\n\n".
      $that->source,
    );
  }
}
