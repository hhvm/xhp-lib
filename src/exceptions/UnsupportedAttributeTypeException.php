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

class XHPUnsupportedAttributeTypeException extends XHPException {
  public function __construct(
    :xhp $that,
    string $type,
    string $attr,
    string $reason,
  ) {
    parent::__construct(
      "Attribute `$attr` in element `".
      :xhp::class2element(get_class($that)).
      "` has unsupported type `$type`: $reason",
    );
  }
}
