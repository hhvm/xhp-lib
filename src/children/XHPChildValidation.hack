/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use namespace Facebook\XHP\ChildValidation as XHPChild;

/** Verify that a new child declaration matches the legacy codegen. */
trait XHPChildValidation {
  require extends x\node;

  abstract protected static function getChildrenDeclaration(
  ): XHPChild\Constraint;

  <<__Override>>
  final protected static function __legacySerializedXHPChildrenDeclaration(
  ): mixed {
    return static::getChildrenDeclaration()->legacySerialize();
  }

  final public function validateChildren(): void {
    invariant(
      $this->__xhpChildrenDeclaration() ===
        x\element::__NO_LEGACY_CHILDREN_DECLARATION,
      "The XHPChildValidation trait can not be used with a 'children' ".
      "declaration; override 'getChildrenDeclaration()'' instead",
    );

    parent::validateChildren();
  }
}
