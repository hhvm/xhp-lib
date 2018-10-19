<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

abstract class :xhp implements XHPChild, JsonSerializable {
  // Must be kept in sync with code generation for XHP
  const string SPREAD_PREFIX = '...$';

  public function __construct(
    KeyedTraversable<string, mixed> $attributes,
    Traversable<XHPChild> $children,
  ): void {
  }
  abstract public function appendChild(mixed $child): this;
  abstract public function prependChild(mixed $child): this;
  abstract public function replaceChildren(...): this;
  abstract public function getChildren(
    ?string $selector = null,
  ): Vector<XHPChild>;
  abstract public function getFirstChild(?string $selector = null): ?XHPChild;
  abstract public function getLastChild(?string $selector = null): ?XHPChild;
  abstract public function getAttribute(string $attr): mixed;
  abstract public function getAttributes(): Map<string, mixed>;
  abstract public function setAttribute(string $attr, mixed $val): this;
  abstract public function setAttributes(
    KeyedTraversable<string, mixed> $attrs,
  ): this;
  abstract public function isAttributeSet(string $attr): bool;
  abstract public function removeAttribute(string $attr): this;
  abstract public function categoryOf(string $cat): bool;
  abstract public function toString(): string;
  /* HH_FIXME[1002] Return collections instead of arrays */
  abstract protected function &__xhpCategoryDeclaration(): array<string, int>;
  abstract protected function &__xhpChildrenDeclaration(): mixed;
  protected static function &__xhpAttributeDeclaration(
  ): array<string, array<int, mixed>> {
    return array();
  }

  public ?string $source;

  /**
   * Enabling validation will give you stricter documents; you won't be able to
   * do many things that violate the XHTML 1.0 Strict spec. It is recommend that
   * you leave this on because otherwise things like the `children` keyword will
   * do nothing. This validation comes at some CPU cost, however, so if you are
   * running a high-traffic site you will probably want to disable this in
   * production. You should still leave it on while developing new features,
   * though.
   */
  private static bool $validateChildren = true;
  private static bool $validateAttributes = false;

  public static function disableChildValidation(): void {
    self::$validateChildren = false;
  }

  public static function enableChildValidation(): void {
    self::$validateChildren = true;
  }

  public static function isChildValidationEnabled(): bool {
    return self::$validateChildren;
  }

  public static function disableAttributeValidation(): void {
    self::$validateAttributes = false;
  }

  public static function enableAttributeValidation(): void {
    self::$validateAttributes = true;
  }

  public static function isAttributeValidationEnabled(): bool {
    return self::$validateAttributes;
  }

  final public function __toString(): string {
    return $this->toString();
  }

  final public function jsonSerialize(): string {
    return $this->toString();
  }

  final protected static function renderChild(XHPChild $child): string {
    if ($child instanceof :xhp) {
      return $child->toString();
    }
    if ($child instanceof XHPUnsafeRenderable) {
      return $child->toHTMLString();
    }
    if ($child instanceof Traversable) {
      throw new XHPRenderArrayException('Can not render traversables!');
    }

    /* HH_FIXME[4281] stringish migration */
    return htmlspecialchars((string)$child);
  }

  public static function element2class(string $element): string {
    return 'xhp_'.str_replace(array(':', '-'), array('__', '_'), $element);
  }

  public static function class2element(string $class): string {
    return str_replace(
      array('__', '_'),
      array(':', '-'),
      preg_replace('#^xhp_#i', '', $class),
    );
  }
}
