/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

final class None implements Constraint {
  public function legacySerialize(): mixed {
    return 0;
  }

  public function legacySerializeAsLeaf(): null {
    return null;
  }
}
