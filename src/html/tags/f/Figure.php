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

class :figure extends :xhp:html-element {
  use XHPChildDeclarationConsistencyValidation;
  category %flow, %sectioning;
  children ((:figcaption, %flow+) | (%flow+, :figcaption?));

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyOf(
      XHPChild\sequence(
        XHPChild\ofType<:figcaption>(),
        XHPChild\atLeastOneOf(XHPChild\category('%flow')),
      ),
      XHPChild\sequence(
        XHPChild\atLeastOneOf(XHPChild\category('%flow')),
        XHPChild\optional(XHPChild\ofType<:figcaption>()),
      ),
    );
  }

  protected string $tagName = 'figure';
}
