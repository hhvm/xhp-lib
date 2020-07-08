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

xhp class line
  extends element
  implements Cat\GraphicsElement, Cat\RenderableElement, Cat\ShapeElement {
  use \XHPChildValidation;

  attribute
    string requiredExtensions,
    string systemLanguage,
    float pathLength,
    // float or <percentage>
    mixed x1,
    // float or <percentage>
    mixed y1,
    // float or <percentage>
    mixed x2,
    // float or <percentage>
    mixed y2;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\AnimationElement>(),
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<Cat\PaintServerElement>(),
      XHPChild\ofType<clipPath>(),
      XHPChild\ofType<marker>(),
      XHPChild\ofType<mask>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<HTML\style>(),
    ));
  }

  protected string $tagName = 'line';
}
