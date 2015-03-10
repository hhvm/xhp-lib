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

class XHPCoreRenderException extends XHPException {
  public function __construct(:xhp $that, mixed $rend) {
    parent::__construct(
      ':x:element::render must reduce an object to an :x:primitive, but `'.
      :xhp::class2element(get_class($that)).'` reduced into `'.
      gettype($rend)."`.\n\n".$that->source
    );
  }
}
