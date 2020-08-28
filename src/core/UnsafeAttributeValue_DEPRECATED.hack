/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP;

/**
 * INCREDIBLY DANGEROUS: Marks an object as being able to provide an HTML
 * string.
 *
 * This is useful when migrating to XHP for attribute values which are already escaped.
 * If the attribute contains unescaped double quotes, this will not escape them, which will break the runtime behavior.
 *
 * This must be used via `forceAttribute()`.
 */
abstract class UnsafeAttributeValue_DEPRECATED {
  abstract public function toHTMLString(): string;

  final public function __toString(): string {
    return $this->toHTMLString();
  }
}
