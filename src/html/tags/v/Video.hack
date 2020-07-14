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

final xhp class video extends element {
  use XHPChild\Validation;
  attribute
    bool autoplay,
    bool controls,
    enum {'anonymous', 'use-credentials'} crossorigin,
    int height,
    bool loop,
    string mediagroup,
    bool muted,
    bool playsinline,
    string poster,
    enum {'none', 'metadata', 'auto'} preload,
    string src,
    int width;
  category %flow, %phrase, %embedded, %interactive;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\any_number_of(XHPChild\of_type<source>()),
      XHPChild\any_number_of(XHPChild\of_type<track>()),
      XHPChild\any_number_of(
        XHPChild\any_of(XHPChild\pcdata(), XHPChild\category('%flow')),
      ),
    );
  }

  protected string $tagName = 'video';
}
