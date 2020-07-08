/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */
namespace Facebook\XHP\SVG;

use namespace Facebook\XHP\HTML;
use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class stop extends element /* implements nothing */ {
  use \XHPChildValidation;

  attribute
    // float or <percentage>
    mixed offset;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<animate>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<set>(),
      XHPChild\ofType<HTML\style>(),
    ));
  }

  protected string $tagName = 'stop';
}
