/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

final class any_number_of<T as Constraint> extends QuantifierConstraint<T> {
  const LegacyExpressionType LEGACY_EXPRESSION_TYPE =
    LegacyExpressionType::ANY_QUANTITY;
}
