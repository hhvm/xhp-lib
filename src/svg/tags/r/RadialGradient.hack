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

xhp class radialGradient extends element {

  attribute
    unknown cx,
    unknown cy,
    unknown r,
    unknown fx,
    unknown fy,
    unknown fr,
    unknown gradientUnits,
    unknown gradientTransform,
    unknown spreadMethod,
    unknown href;

  protected string $tagName = 'radialGradient';
}
