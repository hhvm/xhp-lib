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

xhp class feSpotLight extends element implements Cat\LightSource {
  use \XHPChildValidation;

  attribute
    float x,
    float y,
    float z,
    float pointsAtX,
    float pointsAtY,
    float pointsAtZ,
    float specularExponent,
    float limitingConeAngle;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\anyOf(
      XHPChild\ofType<Cat\DescriptiveElement>(),
      XHPChild\ofType<animate>(),
      XHPChild\ofType<HTML\script>(),
      XHPChild\ofType<set>(),
    ));
  }

  protected string $tagName = 'feSpotLight';
}
