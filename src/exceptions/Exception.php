<?hh // strict
/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
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
