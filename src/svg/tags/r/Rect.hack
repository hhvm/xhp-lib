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

xhp class rect
  extends element
  implements Cat\GraphicsElement, Cat\RenderableElement, Cat\ShapeElement {
  use \XHPChildValidation;

  attribute
    string requiredExtensions,
    string systemLanguage,
    float pathLength,
    float x,
    float y,
    string width,
    string height,
    // <length-pecentage> or "auto"
    string rx,
    // <length-pecentage> or "auto"
    string ry;

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

  protected string $tagName = 'rect';
}
