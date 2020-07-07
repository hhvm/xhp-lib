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

xhp class tspan extends element {

  attribute
    unknown requiredExtensions,
    unknown systemLanguage,
    unknown x,
    unknown y,
    unknown dx,
    unknown dy,
    unknown rotate,
    unknown textLength,
    unknown lengthAdjust;

  protected string $tagName = 'tspan';
}
