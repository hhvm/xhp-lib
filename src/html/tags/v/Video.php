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

class :video extends :xhp:html-element {
  use XHPChildDeclarationConsistencyValidation;
  attribute
    bool autoplay,
    bool controls,
    enum {'anonymous', 'use-credentials'} crossorigin,
    int height,
    bool loop,
    string mediagroup,
    bool muted,
    string poster,
    enum {'none', 'metadata', 'auto'} preload,
    string src,
    int width;
  category %flow, %phrase, %embedded, %interactive;
  children (:source*, :track*, (pcdata | %flow)*);

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\anyNumberOf(XHPChild\ofType<:source>()),
      XHPChild\anyNumberOf(XHPChild\ofType<:track>()),
      XHPChild\anyNumberOf(
        XHPChild\anyOf(XHPChild\pcdata(), XHPChild\category('%flow')),
      ),
    );
  }

  protected string $tagName = 'video';
}
