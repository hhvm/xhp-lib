/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

final xhp class iframe extends pcdata_element {
  attribute
    string allow,
    bool allowfullscreen,
    bool allowpaymentrequest,
    string name,
    int height,
    enum {
      '',
      'no-referrer',
      'no-referrer-when-downgrade',
      'same-origin',
      'origin',
      'strict-origin',
      'origin-when-cross-origin',
      'strict-origin-when-cross-origin',
      'unsafe-url',
    } referrerpolicy,
    string sandbox,
    bool seamless,
    string src,
    string srcdoc,
    int width;
  category %flow, %phrase, %embedded, %interactive;
  protected string $tagName = 'iframe';
}
