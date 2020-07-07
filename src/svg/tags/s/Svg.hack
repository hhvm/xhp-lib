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

xhp class svg extends element {
  // The category is from the html family.
  // This is to allow svg documents to be embedded into HTML.
  // Svg uses it own content model with very different rules and names.
  category %phrase;

  protected string $tagName = 'svg';
}
