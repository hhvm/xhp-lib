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

final xhp class figure
  extends element
  implements Category\Flow, Category\Sectioning, Category\Palpable {
  use XHPChild\Validation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_of(
      XHPChild\sequence(
        XHPChild\of_type<figcaption>(),
        XHPChild\at_least_one_of(XHPChild\of_type<Category\Flow>()),
      ),
      XHPChild\sequence(
        XHPChild\at_least_one_of(XHPChild\of_type<Category\Flow>()),
        XHPChild\optional(XHPChild\of_type<figcaption>()),
      ),
    );
  }

  protected string $tagName = 'figure';
}
