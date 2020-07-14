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

final xhp class details extends element {
  use XHPChild\Validation;
  attribute bool open;
  category %flow, %phrase, %interactive;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\of_type<summary>(),
      XHPChild\at_least_one_of(XHPChild\category('%flow')),
    );
  }

  protected string $tagName = 'details';
}
