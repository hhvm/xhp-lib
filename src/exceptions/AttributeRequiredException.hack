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

class AttributeRequiredException extends namespace\Exception {
  public function __construct(x\node $that, string $attr) {
    parent::__construct(
      'Required attribute `'.
      $attr.
      '` was not specified in element '.
      '`'.
      self::getElementName($that).
      "`.\n\n".
      $that->source,
    );
  }
}
