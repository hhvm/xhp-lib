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

xhp class a
  extends element
  implements Cat\ContainerElement, Cat\RenderableElement {
  use XHPChild\Validation;

  /**
   * Slightly different from `HTML\a`.
   * The difference is in the spec.
   * If you're missing something, look here to see
   * if this attribute should exist on the svg version of <a>:
   * https://svgwg.org/svg2-draft/linking.html#AElement
   */
  attribute
    string requiredExtensions,
    string systemLanguage,
    string href,
    string target,
    // the value given is the suggested filename for the downloaded file
    string download,
    string ping,
    string rel,
    string hreflang,
    string type,
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
    } referrerpolicy;

  /**
   * Spec: Descriptive content, plus any element or text allowed by its parent's content model,
   *       except for another a element. If the parent is a switch element,
   *       use the content model of the nearest ancestor that isn't a switch.
   *
   * Note: We can't validate this, since we can't see our parents.
   */
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any();
  }

  protected string $tagName = 'a';
}
