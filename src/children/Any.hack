/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

final class Any implements Constraint {
  public function legacySerialize(): mixed {
    return 1;
  }

  public function legacySerializeAsLeaf(): (LegacyConstraintType, mixed) {
    return tuple(LegacyConstraintType::ANY, null);
  }
}
