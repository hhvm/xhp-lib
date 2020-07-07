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

xhp class text extends element {

  attribute
    string requiredExtensions,
    string systemLanguage,
    enum {'spacing', 'spacingAndGlyphs'} lengthAdjust,
    // <length-percentage> or float
    mixed x,
    // <length-percentage> or float
    mixed y,
    // <length-percentage> or float
    mixed dx,
    // <length-percentage> or float
    mixed dy,
    unknown rotate,
    // <length-percentage> or float
    mixed textLength;

  protected string $tagName = 'text';
}
