/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

final xhp class style
  extends unescaped_pcdata_element
  implements
    Category\Metadata {
  attribute
    string media,
    bool scoped,
    string type;

  protected string $tagName = 'style';
}
