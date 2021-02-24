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

xhp class feFuncG extends element implements Cat\TransferFunctionElement {
  use XHPChild\Validation;

  attribute
    enum {'identity', 'table', 'discrete', 'linear', 'gamma'} type,
    string tableValues,
    float slope,
    float intercept,
    float amplitude,
    float exponent,
    float offset;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<animate>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<set>(),
    ));
  }

  protected string $tagName = 'feFuncG';
}
