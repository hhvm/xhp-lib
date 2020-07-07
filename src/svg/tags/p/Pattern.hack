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

xhp class pattern extends element {

  attribute
    unknown viewBox,
    string preserveAspectRatio,
    unknown x,
    unknown y,
    int width,
    int height,
    unknown patternUnits,
    unknown patternContentUnits,
    unknown patternTransform,
    string href;

  protected string $tagName = 'pattern';
}
