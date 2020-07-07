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

xhp class feComposite extends element {

  attribute
    unknown clip,
    unknown color-rendering,
    unknown enable-background,
    unknown fill,
    unknown font,
    unknown isolation,
    unknown marker,
    unknown stroke-miterlimit,
    unknown x,
    unknown y,
    unknown width,
    unknown height,
    unknown result,
    unknown in,
    unknown in2,
    unknown operator,
    unknown k1,
    unknown k2,
    unknown k3,
    unknown k4;

  protected string $tagName = 'feComposite';
}
