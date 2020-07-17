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

final xhp class button
  extends element
  implements Cat\PhraseElement, Cat\FlowElement, Cat\InteractiveElement {
  use XHPChild\Validation;
  attribute
    bool disabled,
    string form,
    string formaction,
    string formenctype,
    enum {'get', 'post'} formmethod,
    bool formnovalidate,
    string formtarget,
    string menu,
    string name,
    enum {'submit', 'button', 'reset'} type,
    string value;

  // Should not contain interactive
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(
      XHPChild\any_of(XHPChild\pcdata(), XHPChild\category('%phrase')),
    );
  }

  protected string $tagName = 'button';
}
