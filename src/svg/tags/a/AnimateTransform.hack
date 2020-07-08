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

xhp class animateTransform extends element implements Cat\AnimationElement {

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
    // <number> (but fractions don't make sense) or "indefinite"
    arraykey repeatCount,
    // <Clock-value> or "indefinite"
    string repeatDur,
    string fill,
    string values,
    string keyTimes,
    string keySplines,
    string from,
    string to,
    string by,
    string requiredExtensions,
    string systemLanguage,
    enum {'translate', 'scale', 'rotate', 'skewX', 'skewY'} type;

  protected string $tagName = 'animateTransform';
}
