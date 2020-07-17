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

final xhp class form extends element implements Cat\FlowElement {
  use XHPChild\Validation;
  attribute
    string action,
    string accept-charset,
    enum {'on', 'off'} autocomplete,
    string enctype,
    enum {'get', 'post'} method,
    string name,
    bool novalidate,
    string rel,
    string target;

  // Should not contain :form
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(
      XHPChild\any_of(XHPChild\pcdata(), XHPChild\category('%flow')),
    );
  }

  protected string $tagName = 'form';
}
