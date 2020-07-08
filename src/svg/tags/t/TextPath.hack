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

xhp class textPath
  extends element
  implements
    Cat\GraphicsElement,
    Cat\RenderableElement,
    Cat\TextContentElement,
    Cat\TextContentChildElement {

  attribute
    string requiredExtensions,
    string systemLanguage,
    enum {'spacing', 'spacingAndGlyphs'} lengthAdjust,
    // <length-percentage> or float
    mixed textLength,
    string path,
    string href,
    string startOffset,
    enum {'align', 'stretch'} method,
    enum {'auto', 'exact'} spacing,
    enum {'left', 'right'} side;

  protected string $tagName = 'textPath';
}
