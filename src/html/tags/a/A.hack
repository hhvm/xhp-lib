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

final xhp class a extends element {
  use XHPChild\Validation;

  attribute
    string download,
    string href,
    string hreflang,
    string media,
    string ping,
    enum {
      '',
      'no-referrer',
      'no-referrer-when-downgrade',
      'same-origin',
      'origin',
      'strict-origin',
      'origin-when-cross-origin',
      'strict-origin-when-cross-origin',
      'unsafe-url',
    } referrerpolicy,
    string rel,
    string target,
    string type,
    // Legacy
    string name;
  category %flow, %phrase, %interactive;
  // Should not contain %interactive
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(
      XHPChild\anyOf(XHPChild\pcdata(), XHPChild\category('%flow')),
    );
  }

  protected string $tagName = 'a';
}
