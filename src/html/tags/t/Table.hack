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

final xhp class table extends element {
  use XHPChild\Validation;
  attribute
    int border,
    bool sortable;
  category %flow;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\optional(XHPChild\ofType<caption>()),
      XHPChild\anyNumberOf(XHPChild\ofType<colgroup>()),
      XHPChild\optional(XHPChild\ofType<thead>()),
      XHPChild\anyOf(
        XHPChild\sequence(
          XHPChild\ofType<tfoot>(),
          XHPChild\anyOf(
            XHPChild\atLeastOneOf(XHPChild\ofType<tbody>()),
            XHPChild\anyNumberOf(XHPChild\ofType<tr>()),
          ),
        ),
        XHPChild\sequence(
          XHPChild\anyOf(
            XHPChild\atLeastOneOf(XHPChild\ofType<tbody>()),
            XHPChild\anyNumberOf(XHPChild\ofType<tr>()),
          ),
          XHPChild\optional(XHPChild\ofType<tfoot>()),
        ),
      ),
    );
  }

  protected string $tagName = 'table';
}
