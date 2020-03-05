/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Elements\Core as x;

trait XHPHTMLHelpers implements HasXHPHTMLHelpers {
  require extends x\node;

  /*
   * Appends a string to the "class" attribute (space separated).
   */
  public function addClass(string $class): this {
    $current_class = ($this->getAttributes()['class'] ?? '') as string;
    return $this->setAttribute('class', trim($current_class.' '.$class));
  }

  /*
   * Conditionally adds a class to the "class" attribute.
   */
  public function conditionClass(bool $cond, string $class): this {
    return $cond ? $this->addClass($class) : $this;
  }

  /*
   * Generates a unique ID (and sets it) on the "id" attribute. A unique ID
   * will only be generated if one has not already been set.
   */
  public function requireUniqueID(): string {
    $id = $this->getAttributes()['id'] ?? null;
    if ($id === null || $id === '') {
      $id = bin2hex(random_bytes(5));
      $this->setAttribute('id', $id);
    }
    return (string)$id;
  }

  /*
   * Fetches the "id" attribute, will generate a unique value if not set.
   */
  final public function getID(): string {
    return $this->requireUniqueID();
  }
}
