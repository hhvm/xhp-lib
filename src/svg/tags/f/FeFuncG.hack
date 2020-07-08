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

xhp class feFuncG extends element implements Cat\TranferFunctionElement {
  use \XHPChildValidation;

  attribute
    enum {'identity', 'table', 'discrete', 'linear', 'gamma'} type,
    string tableValues,
    float slope,
    float intercept,
    float amplitude,
    float exponent,
    float offset;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<animate>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<set>(),
    ));
  }

  protected string $tagName = 'feFuncG';
}
