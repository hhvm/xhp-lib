<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class XHPInvalidArrayKeyAttributeException extends XHPException {
  public function __construct(
    :xhp $that,
    string $type,
    string $attr,
    string $val_type,
  ) {
    parent::__construct(
      "Invalid key in attribute `$attr` of type array<$val_type => ?> supplied".
      " to element `".
      :xhp::class2element(get_class($that)).
      "`, expected ".
      "array<$type => ?>.\n\n".
      $that->source,
    );
  }
}
