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

xhp class feComponentTransfer extends element {

  attribute
    string clip,
    enum {
      'auto',
      'optimizeSpeed',
      'optimizeQuality',
      'inherit',
    } color-rendering,
    string enable-background,
    unknown fill,
    unknown font,
    unknown isolation,
    unknown marker,
    unknown x,
    unknown y,
    string width,
    string height,
    string result,
    unknown in;

  protected string $tagName = 'feComponentTransfer';
}
