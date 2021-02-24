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

xhp class feDiffuseLighting extends element implements Cat\FilterPrimitive {
  use XHPChild\Validation;

  attribute
    string clip,
    enum {
      'auto',
      'optimizeSpeed',
      'optimizeQuality',
      'inherit',
    } color-rendering,
    string enable-background,
    string fill,
    string font,
    enum {'auto', 'isolate'} isolation,
    string marker,
    float x,
    float y,
    string width,
    string height,
    string result,
    string in,
    float surfaceScale,
    float diffuseConstant,
    // <number-optional-number>
    string kernelUnitLength;

  /**
   * Spec: Any number of descriptive elements, script
   *       and exactly one light sources element, in any order.
   *
   * Note: We allow any number of LightSources, not just 1.
   */
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<Cat\LightSource>(),
    ));
  }

  protected string $tagName = 'feDiffuseLighting';
}
