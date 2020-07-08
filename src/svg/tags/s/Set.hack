/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */
namespace Facebook\XHP\SVG;

use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class set extends element implements Cat\AnimationElement {

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

  protected string $tagName = 'set';
}
