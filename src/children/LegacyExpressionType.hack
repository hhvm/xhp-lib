/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

enum LegacyExpressionType: int {
  EXACTLY_ONE = 0;
  ANY_QUANTITY = 1;
  ZERO_OR_ONE = 2;
  AT_LEAST_ONE = 3;
  SEQUENCE = 4;
  EITHER = 5;
}
