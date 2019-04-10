<?hh // partial
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class ReflectionXHPClass {
  public function __construct(private classname<:x:composable-element> $className) {
    invariant(
      class_exists($this->className),
      'Invalid class name: %s',
      $this->className,
    );
  }

  public function getReflectionClass(): ReflectionClass {
    return new ReflectionClass($this->getClassName());
  }

  public function getClassName(): classname<:x:composable-element> {
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
