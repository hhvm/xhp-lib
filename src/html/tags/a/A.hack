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

final xhp class a
  extends element
  implements Cat\PhraseElement, Cat\FlowElement, Cat\InteractiveElement {
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

  // Should not contain %interactive
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(
      XHPChild\any_of(XHPChild\pcdata(), XHPChild\of_type<Cat\FlowElement>()),
    );
  }

  protected string $tagName = 'a';
}
