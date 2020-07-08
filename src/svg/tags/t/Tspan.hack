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
  use \XHPChildValidation;

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
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<Cat\PaintServerElement>(),
      XHPChild\ofType<a>(),
      // technically incorrect, we may only allow `SVG\a`
      // but let's not punish you for using the wrong `<a>`
      XHPChild\ofType<HTML\a>(),
      XHPChild\ofType<animate>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<set>(),
      XHPChild\ofType<HTML\style>(),
      XHPChild\ofType<tspan>(),
      XHPChild\pcdata(),
    ));
  }

  protected string $tagName = 'tspan';
}
