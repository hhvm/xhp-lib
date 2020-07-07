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

xhp class line extends element {

  attribute
    string requiredExtensions,
    string systemLanguage,
    unknown pathLength,
    // float or <percentage>
    mixed x1,
    // float or <percentage>
    mixed y1,
    // float or <percentage>
    mixed x2,
    // float or <percentage>
    mixed y2;

  protected string $tagName = 'line';
}
