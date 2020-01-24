/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

enum LegacyConstraintType: int {
  ANY = 1;
  PCDATA = 2;
  CLASSNAME = 3;
  CATEGORY = 4;
  EXPRESSION = 5;
}
