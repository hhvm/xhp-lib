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

class XHPInvalidArrayKeyAttributeException extends XHPException {
  public function __construct(
    :xhp $that,
    string $type,
    string $attr,
    string $val_type,
  ) {
    parent::__construct(
      "Invalid key in attribute `$attr` of type array<$val_type => ?> supplied".
      " to element `".:xhp::class2element(get_class($that))."`, expected ".
      "array<$type => ?>.\n\n".$that->source
    );
  }
}
