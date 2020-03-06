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
use namespace HH\Lib\Str;

class Exception extends \Exception {
  protected static function getElementName(x\xhp $that): string {
    $name = \get_class($that);
    if (Str\starts_with($name, 'xhp_')) {
      return x\xhp::class2element($name);
    }
    return $name;
  }
}
