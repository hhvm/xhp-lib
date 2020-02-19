<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\ChildValidation as XHPChild;

class :optgroup extends :xhp:html-element {
  use XHPChildDeclarationConsistencyValidation;
  attribute
    bool disabled,
    string label;
  children (:option)*;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\ofType<:option>());
  }

  protected string $tagName = 'optgroup';
}
