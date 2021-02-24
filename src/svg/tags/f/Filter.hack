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

xhp class filter extends element /* implements nothing */ {
  use XHPChild\Validation;

  attribute
    string clip,
    enum {
      'auto',
      'optimizeSpeed',
      'optimizeQuality',
      'inherit',
    } color-rendering,
    string enable-background,
    string fill,
    string font,
    enum {'auto', 'isolate'} isolation,
    string marker,
    enum {'true', 'false'} externalResourcesRequired,
    string x,
    string y,
    string width,
    string height,
    enum {'userSpaceOnUse', 'objectBoundingBox'} filterUnits,
    enum {'userSpaceOnUse', 'objectBoundingBox'} primitiveUnits;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<Cat\FilterPrimitive>(),
      XHPChild\of_type<animate>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<set>(),
    ));
  }

  protected string $tagName = 'filter';
}
