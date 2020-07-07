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

xhp class linearGradient extends element {

  attribute
    // float or <percentage>
    mixed x1,
    // float or <percentage>
    mixed y1,
    // float or <percentage>
    mixed x2,
    // float or <percentage>
    mixed y2,
    enum {'userSpaceOnUse', 'objectBoundingBox'} gradientUnits,
    unknown gradientTransform,
    unknown spreadMethod,
    string href;

  protected string $tagName = 'linearGradient';
}
