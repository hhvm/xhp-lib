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

/**
 * Render an <html /> element within a DOCTYPE, XHP has chosen to only support
 * the HTML5 doctype.
 */
class :x:doctype extends :x:primitive {
  children (:html);

  protected function stringify(): string {
    $children = $this->getChildren();
    return '<!DOCTYPE html>' . (:xhp::renderChild($children[0]));
  }
}
