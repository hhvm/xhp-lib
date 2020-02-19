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

class :datalist extends :xhp:html-element {
  use XHPChildDeclarationConsistencyValidation;
  category %flow, %phrase;
  children (%phrase+ | :option*);

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyOf(
      XHPChild\atLeastOneOf(XHPChild\category('%phrase')),
      XHPChild\anyNumberOf(XHPChild\ofType<:option>()),
    );
  }

  protected string $tagName = 'datalist';
}
