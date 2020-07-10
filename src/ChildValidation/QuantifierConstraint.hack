/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

abstract class QuantifierConstraint<T as Constraint>
  implements LegacyExpression {
  abstract const LegacyExpressionType LEGACY_EXPRESSION_TYPE;

  final public function __construct(private T $child) {}

  final public function legacySerialize(
  ): (LegacyExpressionType, mixed, mixed) {
    $inner = $this->child;
    $as_leaf = $inner->legacySerializeAsLeaf();
    if ($as_leaf is nonnull) {
      return tuple(static::LEGACY_EXPRESSION_TYPE, $as_leaf[0], $as_leaf[1]);
    }

    return tuple(
      static::LEGACY_EXPRESSION_TYPE,
      LegacyConstraintType::EXPRESSION,
      $inner->legacySerialize(),
    );
  }

  final public function legacySerializeAsLeaf(): null {
    return null;
  }
}
