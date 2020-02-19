<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\ChildValidation as XHPChild;

class :embed extends :xhp:html-element {
  use XHPChildDeclarationConsistencyValidation;
  attribute
    int height,
    string src,
    string type,
    int width,
    /**
     * The following attributes are Flash specific.
     * Most notable use: youtube video embedding
     */
    bool allowfullscreen,
    enum {'always', 'never'} allowscriptaccess,
    string wmode;

  category %flow, %phrase, %embedded, %interactive;
  children (pcdata | %phrase)*;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(
      XHPChild\anyOf(XHPChild\pcdata(), XHPChild\category('%phrase')),
    );
  }

  protected string $tagName = 'embed';
}
