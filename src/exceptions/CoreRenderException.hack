/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP;

use namespace Facebook\XHP\Elements\Core as x;

class CoreRenderException extends namespace\Exception {
  public function __construct(x\xhp $that, mixed $rend) {
    parent::__construct(
      ':x:element::render must reduce an object to an :x:primitive, but `'.
      x\xhp::class2element(\get_class($that)).
      '` reduced into `'.
      \gettype($rend).
      "`.\n\n".
      $that->source,
    );
  }
}
