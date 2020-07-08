/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */
namespace Facebook\XHP\SVG;

use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class tspan
  extends element
  implements
    Cat\GraphicsElement,
    Cat\RenderableElement,
    Cat\TextContentElement,
    Cat\TextContentChildElement {

  attribute
    string requiredExtensions,
    string systemLanguage,
    float x,
    float y,
    // <length-percentage> or float
    mixed dx,
    // <length-percentage> or float
    mixed dy,
    // (number)+
    string rotate,
    // <length-percentage> or float
    mixed textLength,
    enum {'spacing', 'spacingAndGlyphs'} lengthAdjust;

  protected string $tagName = 'tspan';
}
