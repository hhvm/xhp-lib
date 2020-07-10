/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation\_Private;

use namespace Facebook\XHP\ChildValidation as XHPChild;

function normalize(mixed $x): mixed {
  if (
    $x is (int, int, mixed) &&
    $x[0] === XHPChild\LegacyExpressionType::EXACTLY_ONE &&
    $x[1] === XHPChild\LegacyConstraintType::EXPRESSION
  ) {
    return normalize($x[2]);
  }

  if ($x is (int, mixed, mixed)) {
    return tuple($x[0], normalize($x[1]), normalize($x[2]));
  }

  return $x;
}
