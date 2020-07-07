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

xhp class marker extends element {

  attribute
    string viewBox,
    string preserveAspectRatio,
    // enum{...} or <length-percentage> or float
    mixed refX,
    // enum{...} or <length-percentage> or float
    mixed refY,
    enum {'strokeWidth', 'userSpaceOnUse'} markerUnits,
    // <length-percentage> or float
    mixed markerWidth,
    // <length-percentage> or float
    mixed markerHeight,
    // "auto" or "auto-start-reverse" or <angle> or float
    mixed orient;

  protected string $tagName = 'marker';
}
