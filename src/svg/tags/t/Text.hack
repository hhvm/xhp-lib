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

xhp class text
  extends element
  implements
    Cat\GraphicsElement,
    Cat\RenderableElement,
    Cat\TextContentElement {
  use \XHPChildValidation;

  attribute
    string requiredExtensions,
    string systemLanguage,
    enum {'spacing', 'spacingAndGlyphs'} lengthAdjust,
    // <length-percentage> or float
    mixed x,
    // <length-percentage> or float
    mixed y,
    // <length-percentage> or float
    mixed dx,
    // <length-percentage> or float
    mixed dy,
    // (number)+
    string rotate,
    // <length-percentage> or float
    mixed textLength;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\AnimationElement>(),
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<Cat\PaintServerElement>(),
      XHPChild\ofType<Cat\TextContentChildElement>(),
      XHPChild\ofType<a>(),
      // technically incorrect, we may only allow `SVG\a`
      // but let's not punish you for using the wrong `<a>`
      XHPChild\ofType<HTML\a>(),
      XHPChild\ofType<clipPath>(),
      XHPChild\ofType<marker>(),
      XHPChild\ofType<mask>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<HTML\style>(),
      XHPChild\pcdata(),
    ));
  }

  protected string $tagName = 'text';
}
