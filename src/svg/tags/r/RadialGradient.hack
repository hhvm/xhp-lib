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
    string cx,
    string cy,
    string r,
    string fx,
    string fy,
    string fr,
    enum {'userSpaceOnUse', 'objectBoundingBox'} gradientUnits,
    string gradientTransform,
    enum {'pad', 'reflect', 'repeat'} spreadMethod,
    string href;

  protected string $tagName = 'radialGradient';
}
