/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

use namespace Facebook\XHP\ChildValidation as XHPChild;

/**
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/svg
 */
/* HHAST_FIXME[FinalOrAbstractClass] */
xhp class svg extends element {
  attribute
    string width,
    string height,
    string viewBox,
    string version,
    string xmlns,
    string xmlns:xlink,
    num x,
    num y,
    string preserveAspectRatio,
    string clip-path,
    string clip-rule,
    string color,
    string color-interpolation,
    string color-rendering,
    string cursor,
    string display,
    string fill,
    string fill-opacity,
    string fill-rule,
    string filter,
    string mask,
    string opacity,
    string pointer-events,
    string shape-rendering,
    string stroke,
    string stroke-dasharray,
    string stroke-dashoffset,
    string stroke-linecap,
    string stroke-linejoin,
    string stroke-miterlimit,
    string stroke-opacity,
    string stroke-width,
    string transform,
    string vector-effect,
    string visibility;
  category %phrase;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(
      XHPChild\anyOf(XHPChild\pcdata(), XHPChild\category('%phrase')),
    );
  }

  protected string $tagName = 'svg';
}
