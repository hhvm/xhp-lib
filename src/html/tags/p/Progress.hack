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

final xhp class progress
  extends element
  implements Cat\PhraseElement, Cat\FlowElement {
  use XHPChild\Validation;
  attribute
    float max,
    float value;

  // Should not contain :progress
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(
      XHPChild\any_of(XHPChild\pcdata(), XHPChild\category('%phrase')),
    );
  }

  protected string $tagName = 'progress';
}
