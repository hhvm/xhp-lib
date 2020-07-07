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

xhp class mask extends element {

  attribute
    unknown requiredFeatures,
    unknown requiredExtensions,
    unknown systemLanguage,
    unknown clip,
    unknown color-profile,
    unknown color-rendering,
    unknown enable-background,
    unknown fill,
    unknown font,
    unknown marker,
    unknown stroke-miterlimit,
    unknown x,
    unknown y,
    unknown width,
    unknown height,
    unknown maskUnits,
    unknown maskContentUnits;

  protected string $tagName = 'mask';
}
