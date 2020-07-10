/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

abstract class LeafConstraint implements LegacyExpression {
  abstract public function legacySerializeAsLeaf(
  ): (LegacyConstraintType, mixed);

  final public function legacySerialize(
  ): (LegacyExpressionType, LegacyConstraintType, mixed) {
    $as_leaf = $this->legacySerializeAsLeaf();
    return tuple(LegacyExpressionType::EXACTLY_ONE, $as_leaf[0], $as_leaf[1]);
  }
}
