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

xhp class radialGradient
  extends element
  implements
    Cat\GradientElement,
    Cat\NeverRenderedElement,
    Cat\PaintServerElement {
  use XHPChild\Validation;

  attribute
    string cx,
    string cy,
    string r,
    string fx,
    string fy,
    string fr,
    enum {'userSpaceOnUse', 'objectBoundingBox'} gradientUnits,
    string gradientTransform,
    enum {'pad', 'reflect', 'repeat'} spreadMethod,
    string href;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<animate>(),
      XHPChild\of_type<animateTransform>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<set>(),
      XHPChild\of_type<stop>(),
      XHPChild\of_type<HTML\style>(),
    ));
  }

  protected string $tagName = 'radialGradient';
}
