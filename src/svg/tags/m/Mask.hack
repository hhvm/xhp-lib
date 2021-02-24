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
  use XHPChild\Validation;

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
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\AnimationElement>(),
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<Cat\ShapeElement>(),
      XHPChild\of_type<Cat\StructuralElement>(),
      XHPChild\of_type<Cat\GradientElement>(),
      XHPChild\of_type<a>(),
      // technically incorrect, we may only allow `SVG\a`
      // but let's not punish you for using the wrong `<a>`
      XHPChild\of_type<HTML\a>(),
      XHPChild\of_type<clipPath>(),
      XHPChild\of_type<filter>(),
      XHPChild\of_type<foreignObject>(),
      XHPChild\of_type<image>(),
      XHPChild\of_type<marker>(),
      XHPChild\of_type<mask>(),
      XHPChild\of_type<pattern>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<HTML\style>(),
      XHPChild\of_type<namespace\switch>(),
      XHPChild\of_type<view>(),
      XHPChild\of_type<text>(),
    ));
  }

  protected string $tagName = 'mask';
}
