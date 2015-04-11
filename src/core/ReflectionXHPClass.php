<?hh
/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

class ReflectionXHPClass {
  public function __construct(private string $className) {
    invariant(
      class_exists($this->className),
      'Invalid class name: %s',
      $this->className,
    );
  }

  public function getReflectionClass(): ReflectionClass {
    return new ReflectionClass($this->getClassName());
  }

  public function getClassName(): string {
    return $this->className;
  }

  public function getElementName(): string {
    return :xhp::class2element($this->getClassName());
  }

  public function getChildren(): ReflectionXHPChildrenDeclaration {
    $class = $this->getClassName();
    return $class::__xhpReflectionChildrenDeclaration();
  }

  public function getAttribute(string $name): ReflectionXHPAttribute {
    $map = $this->getAttributes();
    invariant(
      $map->containsKey($name),
      'Tried to get attribute %s for XHP element %s, which does not exist',
      $name,
      $this->getElementName(),
    );
    return $map[$name];
  }

  public function getAttributes(): Map<string, ReflectionXHPAttribute> {
    $class = $this->getClassName();
    return $class::__xhpReflectionAttributes();
  }

  public function getCategories(): Set<string> {
    $class = $this->getClassName();
    return $class::__xhpReflectionCategoryDeclaration();
  }
}
