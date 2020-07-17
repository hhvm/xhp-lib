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

final xhp class ul extends element implements Cat\FlowElement {
  use XHPChild\Validation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\of_type<li>());
  }

  protected string $tagName = 'ul';
}
