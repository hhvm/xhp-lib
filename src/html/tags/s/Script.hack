/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

final xhp class script
  extends unescaped_pcdata_element
  implements
    Category\Phrase,
    Category\Metadata,
    Category\Flow {
  attribute
    bool async,
    string charset,
    enum {'anonymous', 'use-credentials'} crossorigin,
    bool defer,
    bool nomodule,
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
    string src,
    string type,
    string integrity,
    // Legacy
    string language;

  protected string $tagName = 'script';
}
