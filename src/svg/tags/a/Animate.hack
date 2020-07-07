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

xhp class animate extends element {

  attribute
    enum {'replace', 'sum'} additive,
    enum {'none', 'sum'} accumulate,
    string onbegin,
    // Heads-up, HTML defines onended, but SVG defines onend
    string onend,
    string onrepeat,
    string href,
    string attributeName,
    string begin,
    // <Clock-value> or "media" or "indefinite"
    string dur,
    string end,
    // <Clock-value> or "media"
    string min,
    // <Clock-value> or "media"
    string max,
    enum {'always', 'whenNotActive', 'never'} restart,
    // float or "indefinite"
    arraykey repeatCount,
    // <Clock-value> or "indefinite"
    string repeatDur,
    string fill,
    enum {'discrete', 'linear', 'paced', 'spline'} calcMode,
    string values,
    string keyTimes,
    string keySplines,
    string from,
    string to,
    string by,
    string requiredExtensions,
    string systemLanguage;

  protected string $tagName = 'animate';
}
