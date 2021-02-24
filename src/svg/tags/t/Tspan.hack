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

xhp class tspan
  extends element
  implements
    Cat\GraphicsElement,
    Cat\RenderableElement,
    Cat\TextContentElement,
    Cat\TextContentChildElement {
  use XHPChild\Validation;

  attribute
    string requiredExtensions,
    string systemLanguage,
    float x,
    float y,
    // <length-percentage> or float
    mixed dx,
    // <length-percentage> or float
    mixed dy,
    // (number)+
    string rotate,
    // <length-percentage> or float
    mixed textLength,
    enum {'spacing', 'spacingAndGlyphs'} lengthAdjust;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<Cat\PaintServerElement>(),
      XHPChild\of_type<a>(),
      // technically incorrect, we may only allow `SVG\a`
      // but let's not punish you for using the wrong `<a>`
      XHPChild\of_type<HTML\a>(),
      XHPChild\of_type<animate>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<set>(),
      XHPChild\of_type<HTML\style>(),
      XHPChild\of_type<tspan>(),
      XHPChild\pcdata(),
    ));
  }

  protected string $tagName = 'tspan';
}
