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

class AttributeNotSupportedException extends namespace\Exception {
  public function __construct(x\xhp $that, string $attr) {
    parent::__construct(
      'Attribute "'.
      $attr.
      '" is not supported in class '.
      '"'.
      self::getElementName($that).
      '"'.
      "\n\n".
      $that->source.
      "\n\n".
      'Please check for typos in your attribute. If you are creating a new '.
      'attribute on this element define it with the "attribute" keyword'.
      "\n\n",
    );
  }
}
