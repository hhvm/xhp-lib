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

class :ruby extends :xhp:html-element {
  use XHPChildDeclarationConsistencyValidation;
  category %flow, %phrase;
  children (
    (pcdata | :rb)+ | ((:rp, :rt) | (:rp, :rtc) | (:rt, :rp) | (:rtc, :rp))+
  );

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyOf(
      XHPChild\atLeastOneOf(
        XHPChild\anyOf(XHPChild\pcdata(), XHPChild\ofType<:rb>()),
      ),
      XHPChild\atLeastOneOf(XHPChild\anyOf(
        XHPChild\sequence(XHPChild\ofType<:rp>(), XHPChild\ofType<:rt>()),
        XHPChild\sequence(XHPChild\ofType<:rp>(), XHPChild\ofType<:rtc>()),
        XHPChild\sequence(XHPChild\ofType<:rt>(), XHPChild\ofType<:rp>()),
        XHPChild\sequence(XHPChild\ofType<:rtc>(), XHPChild\ofType<:rp>()),
      )),
    );
  }

  protected string $tagName = 'ruby';
}
