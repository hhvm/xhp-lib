/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

use namespace Facebook\XHP\Core as x;

interface HasXHPHTMLHelpers {
  require extends x\node;

  public function addClass(string $class): this;
  public function conditionClass(bool $cond, string $class): this;
  public function requireUniqueID(): string;
  public function getID(): string;
}
