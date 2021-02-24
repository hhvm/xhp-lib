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

xhp class textPath
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
    enum {'spacing', 'spacingAndGlyphs'} lengthAdjust,
    // <length-percentage> or float
    mixed textLength,
    string path,
    string href,
    string startOffset,
    enum {'align', 'stretch'} method,
    enum {'auto', 'exact'} spacing,
    enum {'left', 'right'} side;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<Cat\PaintServerElement>(),
      XHPChild\of_type<a>(),
      // technically incorrect, we may only allow `SVG\a`
      // but let's not punish you for using the wrong `<a>`
      XHPChild\of_type<HTML\a>(),
      XHPChild\of_type<animate>(),
      XHPChild\of_type<clipPath>(),
      XHPChild\of_type<marker>(),
      XHPChild\of_type<mask>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<set>(),
      XHPChild\of_type<HTML\style>(),
      XHPChild\of_type<tspan>(),
      XHPChild\pcdata(),
    ));
  }

  protected string $tagName = 'textPath';
}
