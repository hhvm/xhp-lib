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

xhp class mask
  extends element
  implements Cat\ContainerElement, Cat\NeverRenderedElement {
  use \XHPChildValidation;

  attribute
    string requiredFeatures,
    string requiredExtensions,
    string systemLanguage,
    string clip,
    string color-profile,
    enum {
      'auto',
      'optimizeSpeed',
      'optimizeQuality',
      'inherit',
    } color-rendering,
    string enable-background,
    string fill,
    string font,
    string marker,
    string x,
    string y,
    string width,
    string height,
    enum {'userSpaceOnUse', 'objectBoundingBox'} maskUnits,
    enum {'userSpaceOnUse', 'objectBoundingBox'} maskContentUnits;

  /**
   * Spec: Any number of the following elements, in any order:
   *       animation, descriptive, shape, structural, gradient,
   *       a, clipPath, color-profile, cursor, filter, font, font-face
   *       foreignObject, image, marker, mask, pattern
   *       script, style, switch, view, text, altGlyphDef
   *
   * Note: The following deprecated tags are not included in the children
   *        - color-profile
   *        - cursor
   *        - font
   *        - font-face
   *        - altGlyphDef
   */
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\AnimationElement>(),
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<Cat\ShapeElement>(),
      XHPChild\ofType<Cat\StruturalElement>(),
      XHPChild\ofType<Cat\GradientElement>(),
      XHPChild\ofType<a>(),
      // technically incorrect, we may only allow `SVG\a`
      // but let's not punish you for using the wrong `<a>`
      XHPChild\ofType<HTML\a>(),
      XHPChild\ofType<clipPath>(),
      XHPChild\ofType<filter>(),
      XHPChild\ofType<foreignObject>(),
      XHPChild\ofType<image>(),
      XHPChild\ofType<marker>(),
      XHPChild\ofType<mask>(),
      XHPChild\ofType<pattern>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<HTML\style>(),
      XHPChild\ofType<namespace\switch>(),
      XHPChild\ofType<view>(),
      XHPChild\ofType<text>(),
    ));
  }

  protected string $tagName = 'mask';
}
