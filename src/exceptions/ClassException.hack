/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP;

use namespace Facebook\XHP\Elements\Core as x;

class ClassException extends namespace\Exception {
  public function __construct(x\xhp $that, string $msg) {
    parent::__construct(
      'Exception in class `'.
      self::getElementName($that).
      "`\n\n".
      "$that->source\n\n".
      $msg,
    );
  }
}
