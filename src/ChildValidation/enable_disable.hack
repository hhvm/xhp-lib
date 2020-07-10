/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation\_Private {
  abstract final class Globals {
    public static bool $validateChildren = true;
  }
}

namespace Facebook\XHP\ChildValidation {
  function is_enabled(): bool {
    return _Private\Globals::$validateChildren;
  }

  function enable(): void {
    _Private\Globals::$validateChildren = true;
  }

  function disable(): void {
    _Private\Globals::$validateChildren = false;
  }
}
