<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace HH\Lib\Str;

abstract xhp class xhp implements XHPChild {
  // Must be kept in sync with code generation for XHP
  const string SPREAD_PREFIX = '...$';

  public function __construct(
    KeyedTraversable<string, mixed> $attributes,
    Traversable<XHPChild> $children,
  ): void {
  }
  abstract public function toStringAsync(): Awaitable<string>;
  abstract public function appendChild(mixed $child): this;
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
  abstract protected function __xhpCategoryDeclaration(): darray<string, int>;
  abstract protected function __xhpChildrenDeclaration(): mixed;
  protected static function __xhpAttributeDeclaration(
  ): darray<string, darray<int, mixed>> {
    return darray[];
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

  public static function disableChildValidation(): void {
    self::$validateChildren = false;
  }

  public static function enableChildValidation(): void {
    self::$validateChildren = true;
  }

  public static function isChildValidationEnabled(): bool {
    return self::$validateChildren;
  }

  final protected static async function renderChildAsync(XHPChild $child): Awaitable<string> {
    if ($child is :xhp) {
      return await $child->toStringAsync();
    }
    if ($child is XHPUnsafeRenderable) {
      return await $child->toHTMLStringAsync();
    }
    if ($child is Traversable<_>) {
      throw new XHPRenderArrayException('Can not render traversables!');
    }

    /* HH_FIXME[4281] stringish migration */
    return htmlspecialchars((string)$child);
  }

  public static function element2class(string $element): string {
    if (self::areXHPNamespacesEnabled()) {
      return Str\replace($element, ':', '\\');
    }
    return $element
      |> Str\replace($$, ':', '__')
      |> Str\replace($$, '-', '_')
      |> 'xhp_'.$$;
  }

  public static function class2element(string $class): string {
    if (self::areXHPNamespacesEnabled()) {
      return Str\replace($class, '\\', ':');
    }

    $elem = Str\strip_prefix($class, 'xhp_')
      |> Str\replace($$, '__', ':');
    if (self::areHyphensMangled()) {
      return Str\replace($elem, '_', '-');
    }
    return $elem;
  }

  <<__Memoize>>
  private static function areXHPNamespacesEnabled(): bool {
    return !Str\starts_with(:x:element::class, 'xhp_');
  }

  <<__Memoize>>
  private static function areHyphensMangled(): bool {
    return !(ini_get('hhvm.hack.lang.disable_xhp_element_mangling') ?? false);
  }
}
