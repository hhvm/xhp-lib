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

xhp class feSpecularLighting extends element implements Cat\FilterPrimitive {
  use \XHPChildValidation;

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
    float specularConstant,
    float specularExponent,
    // <number-optional-number>
    string kernelUnitLength;

  /**
   * Spec: Any number of descriptive elements, script
   *       and exactly one light sources element, in any order.
   *
   * Note: We allow any number of LightSources, not just 1.
   */
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<Cat\LightSource>(),
    ));
  }

  protected string $tagName = 'feSpecularLighting';
}
