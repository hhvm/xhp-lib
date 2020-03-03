/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

xhp class iframe extends :xhp:pcdata_element {
  attribute
    bool allowfullscreen,
    string name,
    int height,
    string sandbox,
    bool seamless,
    string src,
    string srcdoc,
    int width;
  category %flow, %phrase, %embedded, %interactive;
  protected string $tagName = 'iframe';
}
