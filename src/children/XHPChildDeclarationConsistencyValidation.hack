/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\ChildValidation as XHPChild;
use namespace Facebook\XHP\Core as x;

/** Verify that a new child declaration matches the legacy codegen. */
trait XHPChildDeclarationConsistencyValidation {
  require extends x\node;

  abstract protected static function getChildrenDeclaration(
  ): XHPChild\Constraint;

  final private static function normalize(mixed $x): mixed {
    if (
      $x is (int, int, mixed) &&
      $x[0] === XHPChild\LegacyExpressionType::EXACTLY_ONE &&
      $x[1] === XHPChild\LegacyConstraintType::EXPRESSION
    ) {
      return self::normalize($x[2]);
    }

    if ($x is (int, mixed, mixed)) {
      return tuple($x[0], self::normalize($x[1]), self::normalize($x[2]));
    }

    return $x;
  }

  final public function validateChildren(): void {
    $old = self::normalize($this->__xhpChildrenDeclaration());
    $new = self::normalize(static::getChildrenDeclaration()->legacySerialize());

    invariant(
      $old === $new,
      "Old and new XHP children declarations differ in class %s.\nOld\n---\n\n%s\n\nNew\n---\n\n%s\n---\n\n%s",
      static::class,
      \var_export($old, true),
      \var_export($new, true),
      \var_export(static::getChildrenDeclaration(), true),
    );
    parent::validateChildren();
  }
}
