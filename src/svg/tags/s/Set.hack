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

xhp class set extends element {

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
    unknown repeatCount,
    unknown repeatDur,
    string fill,
    string requiredExtensions,
    string systemLanguage,
    unknown to;

  protected string $tagName = 'set';
}
