/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

xhp class link extends singleton {
  attribute
    string as,
    enum {'anonymous', 'use-credentials'} crossorigin,
    string href,
    string hreflang,
    string media,
    string rel @required,
    string sizes,
    string type;
  category %metadata, %phrase, %flow;
  protected string $tagName = 'link';
}
