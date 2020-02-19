<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

/**
 * Subclasses of :xhp:html-singleton may not contain children. When
 * rendered they will be in singleton (<img />, <br />) form.
 */
use namespace Facebook\XHP\ChildValidation as XHPChild;

abstract class :xhp:html-singleton extends :xhp:html-element {
  use XHPChildValidation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\empty();
  }


  protected function stringify(): string {
    return $this->renderBaseAttrs().'>';
  }
}
