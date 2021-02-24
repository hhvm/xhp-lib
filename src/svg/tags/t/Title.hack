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

xhp class title
  extends element
  implements Cat\DescriptiveElement, Cat\NeverRenderedElement {
  use XHPChild\Validation;

  /**
   * Spec: Any elements or character data.
   *
   * Note: It is unclear the me if this means all SVG elements,
   *       or all elements (including HTML and other SGML applications).
   *       Let's err on the side of caution.
   */
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any();
  }

  protected string $tagName = 'title';
}
