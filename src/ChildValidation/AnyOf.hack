/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

use namespace HH\Lib\{C, Vec};

final class any_of<T as Constraint> implements LegacyExpression {
  private vec<T> $children;
  public function __construct(T $a, T $b, T ...$rest) {
    $this->children = Vec\concat(vec[$a, $b], $rest);
  }

  public function legacySerialize(): (LegacyExpressionType, mixed, mixed) {
    $it = tuple(
      LegacyExpressionType::EITHER,
      $this->children[0]->legacySerialize(),
      $this->children[1]->legacySerialize(),
    );
    $rest = Vec\drop($this->children, 2);
    while (!C\is_empty($rest)) {
      $it = tuple(
        LegacyExpressionType::EITHER,
        $it,
        $rest[0]->legacySerialize(),
      );
      $rest = Vec\drop($rest, 1);
    }
    return $it;
  }

  final public function legacySerializeAsLeaf(): null {
    return null;
  }
}
