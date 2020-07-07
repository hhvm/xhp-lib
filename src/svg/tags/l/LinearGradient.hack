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
    unknown x1,
    unknown y1,
    unknown x2,
    unknown y2,
    unknown gradientUnits,
    unknown gradientTransform,
    unknown spreadMethod,
    unknown href;

  protected string $tagName = 'linearGradient';
}
