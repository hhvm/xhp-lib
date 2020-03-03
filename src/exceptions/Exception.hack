/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class XHPException extends Exception {
  protected static function getElementName(:xhp $that): string {
    $name = get_class($that);
    if (substr($name, 0, 4) !== 'xhp_') {
      return $name;
    } else {
      return :xhp::class2element($name);
    }
  }
}
