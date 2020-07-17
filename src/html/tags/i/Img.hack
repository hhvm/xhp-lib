/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

final xhp class img
  extends singleton
  implements Cat\PhraseElement, Cat\FlowElement {
  attribute
    string alt,
    enum {'anonymous', 'use-credentials'} crossorigin,
    enum {'async', 'auto', 'sync'} decoding,
    int height,
    bool ismap,
    enum {'eager', 'lazy'} loading,
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
    string sizes,
    string src,
    string srcset,
    string usemap,
    int width;

  protected string $tagName = 'img';
}
