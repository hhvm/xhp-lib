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
