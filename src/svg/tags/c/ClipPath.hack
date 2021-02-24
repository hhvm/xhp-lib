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

xhp class clipPath
  extends element
  implements Cat\ContainerElement, Cat\NeverRenderedElement {
  use XHPChild\Validation;

  attribute
    string requiredFeatures,
    string requiredExtensions,
    string systemLanguage,
    // rect() or "auto"
    string clip,
    // 	"auto" or "sRGB" or <name> or <iri> or "inherit"
    string color-profile,
    enum {
      'auto',
      'optimizeSpeed',
      'optimizeQuality',
      'inherit',
    } color-rendering,
    // "accumulate" or "new" or [ <x> <y> <width> <height> ] or "inherit"
    string enable-background,
    string fill,
    enum {'true', 'false'} externalResourcesRequired,
    enum {'userSpaceOnUse', 'objectBoundingBox'} clipPathUnits;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<Cat\AnimationElement>(),
      XHPChild\of_type<Cat\ShapeElement>(),
      XHPChild\of_type<text>(),
      XHPChild\of_type<namespace\use>(),
      XHPChild\of_type<HTML\script>(),
    ));
  }

  protected string $tagName = 'clipPath';
}
