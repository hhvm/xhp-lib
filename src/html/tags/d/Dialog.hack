/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class dialog extends :xhp:html_element {
  use XHPChildValidation;
  attribute bool open;
  category %flow, %sectioning;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\category('%flow');
  }

  protected string $tagName = 'dialog';
}
