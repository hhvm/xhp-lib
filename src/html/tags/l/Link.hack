/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

final xhp class link
  extends singleton
  implements
    Category\Phrase,
    Category\Metadata,
    Category\Flow {
  attribute
    string as,
    string color,
    enum {'anonymous', 'use-credentials'} crossorigin,
    bool disabled,
    string href,
    string hreflang,
    string imagesizes,
    string imagesrcset,
    string integrity,
    string media,
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
    string rel @required,
    string sizes,
    string type;

  protected string $tagName = 'link';
}
