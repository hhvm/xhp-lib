/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

use namespace HH\Lib\Str;

final class Category extends LeafConstraint {
  public function __construct(private string $category) {
  }

  <<__Override>>
  public function legacySerializeAsLeaf(): (LegacyConstraintType, string) {
    return tuple(
      LegacyConstraintType::CATEGORY,
      $this->category
        |> Str\strip_prefix($$, '%')
        |> Str\replace($$, ':', '__')
        |> Str\replace($$, '-', '_'),
    );
  }
}
