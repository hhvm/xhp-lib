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

final xhp class menu extends element implements Cat\FlowElement {
  use XHPChild\Validation;
  attribute
    string label,
    enum {'popup', 'toolbar'} type;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_of(
      XHPChild\any_number_of(XHPChild\any_of(
        XHPChild\of_type<menuitem>(),
        XHPChild\of_type<hr>(),
        XHPChild\of_type<menu>(),
      )),
      XHPChild\any_number_of(XHPChild\of_type<li>()),
      XHPChild\any_number_of(XHPChild\of_type<Cat\FlowElement>()),
    );
  }

  protected string $tagName = 'menu';
}
