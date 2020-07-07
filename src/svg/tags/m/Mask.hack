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
    string requiredExtensions,
    string systemLanguage,
    string clip,
    string color-profile,
    enum {
      'auto',
      'optimizeSpeed',
      'optimizeQuality',
      'inherit',
    } color-rendering,
    string enable-background,
    string fill,
    string font,
    string marker,
    string x,
    string y,
    string width,
    string height,
    unknown maskUnits,
    unknown maskContentUnits;

  protected string $tagName = 'mask';
}
