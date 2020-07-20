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

final xhp class datalist
  extends element
  implements Category\Phrase, Category\Flow {
  use XHPChild\Validation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_of(
      XHPChild\at_least_one_of(XHPChild\of_type<Category\Phrase>()),
      XHPChild\any_number_of(XHPChild\of_type<option>()),
    );
  }

  protected string $tagName = 'datalist';
}
