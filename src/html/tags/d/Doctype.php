<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace HH\Lib\C;

/**
 * Render an <html /> element within a DOCTYPE, XHP has chosen to only support
 * the HTML5 doctype.
 */
use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class x:doctype extends :x:primitive {
  use XHPChildValidation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\ofType<:html>();
  }


  protected async function stringifyAsync(): Awaitable<string> {
    return '<!DOCTYPE html>'.(await :xhp::renderChildAsync(C\onlyx($this->getChildren())));
  }
}
