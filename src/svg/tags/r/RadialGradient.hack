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
  use \XHPChildValidation;

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
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<animate>(),
      XHPChild\ofType<animateTransform>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<set>(),
      XHPChild\ofType<stop>(),
      XHPChild\ofType<HTML\style>(),
    ));
  }

  protected string $tagName = 'radialGradient';
}
