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

class :dl extends :xhp:html-element {
  use XHPChildDeclarationConsistencyValidation;
  category %flow;
  children (:dt+, :dd+)*;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\sequence(
      XHPChild\atLeastOneOf(XHPChild\ofType<:dt>()),
      XHPChild\atLeastOneOf(XHPChild\ofType<:dd>()),
    ));
  }

  protected string $tagName = 'dl';
}
