/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

final xhp class template
  extends element
  implements Cat\PhraseElement, Cat\MetadataElement, Cat\FlowElement {

  // The children declaration for this element is extraordinarily verbose so
  // I leave it to you to use it appropriately.
  protected string $tagName = 'template';
}
