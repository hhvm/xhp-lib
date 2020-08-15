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

final xhp class hgroup
  extends element
  implements Category\Flow, Category\Heading, Category\Palpable {
  use XHPChild\Validation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\at_least_one_of(XHPChild\any_of(
      XHPChild\of_type<h1>(),
      XHPChild\of_type<h2>(),
      XHPChild\of_type<h3>(),
      XHPChild\of_type<h4>(),
      XHPChild\of_type<h5>(),
      XHPChild\of_type<h6>(),
    ));
  }

  protected string $tagName = 'hgroup';
}
