/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class dl extends element {
  use XHPChild\Validation;
  category %flow;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\sequence(
      XHPChild\atLeastOneOf(XHPChild\ofType<dt>()),
      XHPChild\atLeastOneOf(XHPChild\ofType<dd>()),
    ));
  }

  protected string $tagName = 'dl';
}
