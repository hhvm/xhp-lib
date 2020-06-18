/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

xhp class area extends singleton {
  attribute
    string alt,
    string coords,
    string download,
    string href,
    bool hreflang,
    string media,
    string ping,
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
    string rel,
    enum {
      'circ',
      'circle',
      'default',
      'poly',
      'polygon',
      'rect',
      'rectangle',
    } shape,
    string target,
    string type;
  category %flow, %phrase;
  protected string $tagName = 'area';
}
