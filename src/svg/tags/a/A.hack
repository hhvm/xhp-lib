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

  protected string $tagName = 'a';
}
