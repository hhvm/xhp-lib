<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class XHPInvalidArrayAttributeException extends XHPException {
  public function __construct(
    :xhp $that,
    string $type,
    string $attr,
    mixed $val,
  ) {
    if (is_object($val)) {
      $val_type = get_class($val);
    } else {
      $val_type = gettype($val);
    }
    parent::__construct(
      "Invalid attribute `$attr` of type array<`$val_type`> supplied to ".
      "element `".
      :xhp::class2element(get_class($that)).
      "`, expected ".
      "array<`$type`>.\n\n".
      $that->source,
    );
  }
}
