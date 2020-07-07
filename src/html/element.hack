/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

use namespace Facebook\XHP\Core as x;

/**
 * This is the base library of HTML elements for use in XHP. This includes all
 * non-deprecated tags and attributes. Elements in this file should stay as
 * close to spec as possible. Facebook-specific extensions should go into their
 * own elements.
 */
abstract xhp class element extends x\primitive {
  use x\TagLikeRenderable;
  use XHPHTMLHelpers;
  use GlobalAttributes;
  use EventAttributes;

  attribute
    // Global HTML attributes
    // Not to be confused with `global attributes`
    string class,
    string contextmenu,
    string id,
    bool inert,
    string role;
}
