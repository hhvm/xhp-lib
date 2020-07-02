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
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/path
 */
final xhp class path extends svg {
  attribute
    string d,
    int pathLength;
  protected string $tagName = 'path';
}
