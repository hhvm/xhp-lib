/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\SVG;

use namespace Facebook\XHP\HTML;
use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class svg
  extends element
  implements Cat\ContainerElement, Cat\RenderableElement, Cat\StruturalElement, HTML\Category\Phrase {
  use XHPChild\Validation;

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

  /**
   * Spec: Any number of the following elements, in any order:
   *       animation, descriptive, paint server, shape, structural
   *       a, audio, canvas, clipPath, filter, foreignObject, iframe,
   *       image, marker, mask, script, style, switch, text, video, view
   *
   * Note: Let's be forgiving and allow all known HTML and SVG elements.
   *       For example `<filter>`, `<mpath>`, `<stop>`, `<view>`, can not
   *       be used otherwise, since they have no category.
   *       We're only banning pcdata, but that seems like the right thing to do.
   */
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<element>(),
      XHPChild\of_type<HTML\element>(),
    ));
  }

  protected string $tagName = 'svg';
}
