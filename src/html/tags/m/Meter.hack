/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class meter extends :xhp:html_element {
  use XHPChildValidation;
  attribute
    float high,
    float low,
    float max,
    float min,
    float optimum,
    float value;
  category %flow, %phrase;
  // Should not contain :meter
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(
      XHPChild\anyOf(XHPChild\pcdata(), XHPChild\category('%phrase')),
    );
  }

  protected string $tagName = 'meter';
}
