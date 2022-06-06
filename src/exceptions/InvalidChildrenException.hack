/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP;

use namespace Facebook\XHP\Core as x;

final class InvalidChildrenException extends namespace\Exception {
  public function __construct(x\node $that, int $index) {
    parent::__construct(
      'Element `'.
      self::getElementName($that).
      '` was rendered with '.
      "invalid children.\n\n".
      $that->__getSourcePositionWithErrorDefaultForNull().
      "\n\n".
      'Verified '.
      $index.
      " children before failing.\n\n".
      "Children expected:\n".
      $that->__getChildrenDeclaration().
      "\n\n".
      "Children received:\n".
      $that->__getChildrenDescription(),
    );
  }
}
