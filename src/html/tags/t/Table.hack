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

final xhp class table extends element implements Category\Flow {
  use XHPChild\Validation;
  attribute
    int border,
    bool sortable;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\optional(XHPChild\of_type<caption>()),
      XHPChild\any_number_of(XHPChild\of_type<colgroup>()),
      XHPChild\optional(XHPChild\of_type<thead>()),
      XHPChild\any_of(
        XHPChild\sequence(
          XHPChild\of_type<tfoot>(),
          XHPChild\any_of(
            XHPChild\at_least_one_of(XHPChild\of_type<tbody>()),
            XHPChild\any_number_of(XHPChild\of_type<tr>()),
          ),
        ),
        XHPChild\sequence(
          XHPChild\any_of(
            XHPChild\at_least_one_of(XHPChild\of_type<tbody>()),
            XHPChild\any_number_of(XHPChild\of_type<tr>()),
          ),
          XHPChild\optional(XHPChild\of_type<tfoot>()),
        ),
      ),
    );
  }

  protected string $tagName = 'table';
}
