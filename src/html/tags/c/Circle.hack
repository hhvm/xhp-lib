/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

/**
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/circle
 */
final xhp class circle extends svg {
  attribute
    string cx,
    string cy,
    string r;
  protected string $tagName = 'circle';
}
