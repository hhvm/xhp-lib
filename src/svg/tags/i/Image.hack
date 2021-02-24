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

xhp class image
  extends element
  implements
    Cat\GraphicsElement,
    Cat\GraphicsReferencingElement,
    Cat\RenderableElement,
    Cat\StruturallyExternalElement {
  use XHPChild\Validation;

  attribute
    string requiredExtensions,
    string systemLanguage,
    string preserveAspectRatio,
    string href,
    enum {'anonymous', 'use-credentials'} crossorigin,
    float x,
    float y,
    string width,
    string height;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\AnimationElement>(),
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<clipPath>(),
      XHPChild\of_type<marker>(),
      XHPChild\of_type<mask>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<HTML\style>(),
    ));
  }

  protected string $tagName = 'image';
}
