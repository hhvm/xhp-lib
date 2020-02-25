<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

xhp class meta extends :xhp:html_singleton {
  attribute
    // The correct definition of http-equiv is an enum, but there are legacy
    // values still used and any strictness here would only be frustrating.
    string charset,
    string content @required,
    string http-equiv,
    string name,
    // Facebook OG
    string property;
  // If itemprop is present, this element is allowed within the <body>.
  category %metadata, %flow, %phrase;
  protected string $tagName = 'meta';
}
