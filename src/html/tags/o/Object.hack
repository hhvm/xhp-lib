/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

use namespace Facebook\XHP\ChildValidation as XHPChild;

final xhp class object extends element {
  use XHPChild\Validation;
  attribute
    string data,
    int height,
    string form,
    string name,
    string type,
    bool typemustmatch,
    string usemap,
    int width;
  category %flow, %phrase, %embedded, %interactive;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\anyNumberOf(XHPChild\ofType<param>()),
      XHPChild\anyNumberOf(
        XHPChild\anyOf(XHPChild\pcdata(), XHPChild\category('%flow')),
      ),
    );
  }

  protected string $tagName = 'object';
}
