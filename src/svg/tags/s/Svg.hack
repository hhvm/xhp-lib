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

xhp class svg extends element {
  // The category is from the html family.
  // This is to allow svg documents to be embedded into HTML.
  // Svg uses it own content model with very different rules and names.
  category %phrase;

  attribute
    string xmlns,
    string requiredExtensions,
    string systemLanguage,
    string onunload,
    string viewBox,
    string preserveAspectRatio,
    float x,
    float y,
    string width,
    string height,
    // only valid in SVG 1.1 and below
    // leaving it in here, since many svg documents
    // specify their version as `1.0` or `1.1`.
    // This is valid.
    // However, doing so may make some attributes / elements
    // unavailable to you, since these elements are from the SVG2 spec.
    // You'll not be able to use attributes which were deprecated or removed
    // in SVG2, since they have been removed from the xhp classes.
    // Declare a SVG1 version in your application code if you need them.
    string version;

  protected string $tagName = 'svg';
}
