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

xhp class set extends element implements Cat\AnimationElement {
  use XHPChild\Validation;

  attribute
    string onbegin,
    string onend,
    string onrepeat,
    string href,
    string attributeName,
    string begin,
    string dur,
    string end,
    string min,
    string max,
    enum {'always', 'whenNotActive', 'never'} restart,
    // <number> (but fractions don't make sense)  or "indefinite"
    arraykey repeatCount,
    // <Clock-value> or "indefinite"
    string repeatDur,
    string fill,
    string requiredExtensions,
    string systemLanguage,
    string to;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(XHPChild\any_of(
      XHPChild\of_type<Cat\DescriptiveElement>(),
      XHPChild\of_type<HTML\script>(),
      XHPChild\of_type<HTML\style>(),
    ));
  }

  protected string $tagName = 'set';
}
