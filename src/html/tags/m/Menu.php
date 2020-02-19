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

class :menu extends :xhp:html-element {
  use XHPChildValidation;
  attribute
    string label,
    enum {'popup', 'toolbar'} type;
  category %flow;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyOf(
      XHPChild\anyNumberOf(XHPChild\anyOf(
        XHPChild\ofType<:menuitem>(),
        XHPChild\ofType<:hr>(),
        XHPChild\ofType<:menu>(),
      )),
      XHPChild\anyNumberOf(XHPChild\ofType<:li>()),
      XHPChild\anyNumberOf(XHPChild\category('%flow')),
    );
  }

  protected string $tagName = 'menu';
}
