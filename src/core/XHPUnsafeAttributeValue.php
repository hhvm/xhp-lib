<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

/**
 * INCREDIBLY DANGEROUS: Marks an object as being able to provide an HTML
 * string.
 *
 * This is useful for attribute values that contain html entities which should
 * not be escaped, such as an onload attribute which can contain a snippet of JS.
 */
abstract class XHPUnsafeAttributeValue implements Stringish {
  abstract public function toHTMLString(): string;

  final public function __toString(): string {
    return $this->toHTMLString();
  }
}
