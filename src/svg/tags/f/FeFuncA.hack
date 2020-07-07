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

xhp class feFuncA extends element {

  attribute
    unknown type,
    unknown tableValues,
    unknown slope,
    unknown intercept,
    float amplitude,
    unknown exponent,
    unknown offset;

  protected string $tagName = 'feFuncA';
}
