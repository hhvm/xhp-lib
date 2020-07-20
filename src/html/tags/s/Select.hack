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

final xhp class select
  extends element
  implements
    Category\Phrase,
    Category\Flow,
    Category\Interactive {
  use XHPChild\Validation;
  attribute
    string autocomplete,
    bool disabled,
    string form,
    bool multiple,
    string name,
    bool required,
    int size;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(
      XHPChild\any_of(XHPChild\of_type<option>(), XHPChild\of_type<optgroup>()),
    );
  }

  protected string $tagName = 'select';
}
