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
    unknown onbegin,
    unknown onend,
    unknown onrepeat,
    string href,
    string attributeName,
    string begin,
    string dur,
    unknown end,
    unknown min,
    unknown max,
    unknown restart,
    unknown repeatCount,
    unknown repeatDur,
    string fill,
    string requiredExtensions,
    string systemLanguage,
    unknown to;

  protected string $tagName = 'set';
}
