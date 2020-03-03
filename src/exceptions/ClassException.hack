/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class XHPClassException extends XHPException {
  public function __construct(:xhp $that, string $msg) {
    parent::__construct(
      'Exception in class `'.
      XHPException::getElementName($that).
      "`\n\n".
      "$that->source\n\n".
      $msg,
    );
  }
}
