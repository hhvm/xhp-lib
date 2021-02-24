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

xhp class switch
  extends element
  implements Cat\ContainerElement, Cat\RenderableElement {
  use XHPChild\Validation;

  attribute
    string requiredExtensions,
    string systemLanguage;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\AnimationElement>(),
      XHPChild\of_type<Cat\ShapeElement>(),
      XHPChild\of_type<a>(),
      // technically incorrect, we may only allow `SVG\a`
      // but let's not punish you for using the wrong `<a>`
      XHPChild\of_type<HTML\a>(),
      XHPChild\of_type<HTML\audio>(),
      XHPChild\of_type<HTML\canvas>(),
      XHPChild\of_type<foreignObject>(),
      XHPChild\of_type<g>(),
      XHPChild\of_type<HTML\iframe>(),
      XHPChild\of_type<image>(),
      XHPChild\of_type<svg>(),
      XHPChild\of_type<namespace\switch>(),
      XHPChild\of_type<text>(),
      XHPChild\of_type<HTML\video>(),
    ));
  }

  protected string $tagName = 'switch';
}
