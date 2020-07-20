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

final xhp class ruby
  extends element
  implements Category\Phrase, Category\Flow {
  use XHPChild\Validation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_of(
      XHPChild\at_least_one_of(
        XHPChild\any_of(XHPChild\pcdata(), XHPChild\of_type<rb>()),
      ),
      XHPChild\at_least_one_of(XHPChild\any_of(
        XHPChild\sequence(XHPChild\of_type<rp>(), XHPChild\of_type<rt>()),
        XHPChild\sequence(XHPChild\of_type<rp>(), XHPChild\of_type<rtc>()),
        XHPChild\sequence(XHPChild\of_type<rt>(), XHPChild\of_type<rp>()),
        XHPChild\sequence(XHPChild\of_type<rtc>(), XHPChild\of_type<rp>()),
      )),
    );
  }

  protected string $tagName = 'ruby';
}
