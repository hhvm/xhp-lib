<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use type Facebook\TypeAssert\IncorrectTypeException;
use namespace Facebook\TypeAssert;
use namespace HH\Lib\{C, Dict, Keyset, Str, Vec};

abstract xhp class x:composable_element extends :xhp {
  protected bool $__isRendered = false;
  private dict<string, mixed> $attributes = dict[];
  private vec<XHPChild> $children = vec[];
  private dict<string, mixed> $context = dict[];

  protected function init(): void {
  }

  /**
   * A new :x:composable_element is instantiated for every literal tag
   * expression in the script.
   *
   * The following code:
   * $foo = <foo attr="val">bar</foo>;
   *
   * will execute something like:
   * $foo = new xhp_foo(array('attr' => 'val'), array('bar'));
   *
   * @param $attributes    map of attributes to values
   * @param $children      list of children
   * @param $debug_info    will in the source when childValidation is enabled
   */
  final public function __construct(
    KeyedTraversable<string, mixed> $attributes,
    Traversable<XHPChild> $children,
    dynamic ...$debug_info
  ) {
    parent::__construct($attributes, $children);
    foreach ($children as $child) {
      $this->appendChild($child);
    }

    foreach ($attributes as $key => $value) {
      if (self::isSpreadKey($key)) {
        invariant(
          $value is :x:composable_element,
          "Only XHP can be used with an attribute spread operator",
        );
        $this->spreadElementImpl($value);
      } else {
        $this->setAttribute($key, $value);
      }
    }

    if (:xhp::isChildValidationEnabled()) {
      if (C\count($debug_info) >= 2) {
        $this->source = $debug_info[0].':'.$debug_info[1];
      } else {
        $this->source =
          'You have child validation on, but debug information is not being '.
          'passed to XHP objects correctly. Ensure xhp.include_debug is on '.
          'in your server configuration. Without this option enabled, '.
          'validation errors will be painful to debug at best.';
      }
    }
    $this->init();
  }

  /**
   * Adds a child to the end of this node. If you give a Traversable to this method
   * then it will behave like a DocumentFragment.
   *
   * @param $child     single child or a Traversable of children
   */
  final public function appendChild(mixed $child): this {
    invariant(!$this->__isRendered, "Can't appendChild after render");
    if ($child is Traversable<_>) {
      foreach ($child as $c) {
        $this->appendChild($c);
      }
    } else if ($child is :x:frag) {
      foreach ($child->getChildren() as $new_child) {
        $this->children[] = $new_child;
      }
    } else if ($child !== null) {
      assert($child is XHPChild);
      $this->children[] = $child;
    }
    return $this;
  }

  /**
   * Replaces all children in this node.
   *
   * @param $children  single child or a Traversable of children
   */
  final public function replaceChildren(XHPChild ...$children): this {
    invariant(!$this->__isRendered, "Can't appendChild after render");
    // This function has been micro-optimized
    $new_children = vec[];
    foreach ($children as $xhp) {
      if ($xhp is :x:frag) {
        foreach ($xhp->children as $child) {
          $new_children[] = $child;
        }
      } else if (!($xhp is Traversable<_>)) {
        $new_children[] = $xhp;
      } else {
        foreach ($xhp as $element) {
          if ($element is :x:frag) {
            foreach ($element->children as $child) {
              $new_children[] = $child;
            }
          } else if ($element !== null) {
            $new_children[] = $element as XHPChild;
          }
        }
      }
    }
    $this->children = $new_children;
    return $this;
  }

  /**
   * Fetches all direct children of this element that match a particular tag
   * name or category (or all children if none is given)
   *
   * @param $selector   tag name or category (optional)
   */
  final public function getChildren(
    ?string $selector = null,
  ): vec<XHPChild> {
    if($selector is null || $selector === ''){
      return $this->children;
    }

    $children = vec[];
    if ($selector[0] == '%') {
      $selector = Str\slice($selector, 1);
      foreach ($this->children as $child) {
        if ($child is :xhp && $child->categoryOf($selector)) {
          $children[] = $child;
        }
      }
    } else {
      $selector = :xhp::element2class($selector);
      foreach ($this->children as $child) {
        if (is_a($child, $selector, /* allow strings = */ true)) {
          $children[] = $child;
        }
      }
    }

    return $children;
  }


  /**
   * Fetches the first direct child of the element, or the first child that
   * matches the tag if one is given
   *
   * @param $selector  tag name or category (optional)
   * @return           the first child node (with the given selector),
   *                       null if there are no (matching) children
   */
  final public function getFirstChild(?string $selector = null): ?XHPChild {
    if ($selector === null) {
      return $this->children[0] ?? null;
    } else if ($selector[0] == '%') {
      $selector = substr($selector, 1);
      foreach ($this->children as $child) {
        if ($child is :xhp && $child->categoryOf($selector)) {
          return $child;
        }
      }
    } else {
      $selector = :xhp::element2class($selector);
      foreach ($this->children as $child) {
        if (is_a($child, $selector, /* allow strings = */ true)) {
          return $child;
        }
      }
    }
    return null;
  }

  /**
   * Fetches the last direct child of the element, or the last child that
   * matches the tag or category if one is given
   *
   * @param $selector  tag name or category (optional)
   * @return           the last child node (with the given selector),
   *                       null if there are no (matching) children
   */
  final public function getLastChild(?string $selector = null): ?XHPChild {
    return $this->getChildren($selector) |> C\last($$);
  }

  /**
   * Fetches an attribute from this elements attribute store. If $attr is not
   * defined in the store and is not a data- or aria- attribute an exception
   * will be thrown. An exception will also be thrown if $attr is required and
   * not set.
   *
   * @param $attr      attribute to fetch
   * @return           value
   */
  final public function getAttribute(string $attr): mixed {
    // Return the attribute if it's there
    if (C\contains_key($this->attributes, $attr)) {
      return $this->attributes[$attr];
    }

    if (!ReflectionXHPAttribute::IsSpecial($attr)) {
      // Get the declaration
      $decl = static::__xhpReflectionAttribute($attr);

      if ($decl === null) {
        throw new XHPAttributeNotSupportedException($this, $attr);
      } else if ($decl->isRequired()) {
        throw new XHPAttributeRequiredException($this, $attr);
      } else {
        return $decl->getDefaultValue();
      }
    } else {
      return null;
    }
  }

  final public static function __xhpReflectionAttribute(
    string $attr,
  ): ?ReflectionXHPAttribute {
    return static::__xhpReflectionAttributes()[$attr] ?? null;
  }

  <<__MemoizeLSB>>
  final public static function __xhpReflectionAttributes(
  ): dict<string, ReflectionXHPAttribute> {
    $decl = static::__xhpAttributeDeclaration();
    return Dict\map_with_key(
      $decl, 
      ($name, $attr_decl) ==> new ReflectionXHPAttribute($name, $attr_decl)
    );
  }

  protected static function __legacySerializedXHPChildrenDeclaration(): mixed {
    $decl = self::emptyInstance()->__xhpChildrenDeclaration();
    if ($decl === self::__NO_LEGACY_CHILDREN_DECLARATION) {
      return 1; // any children
    }
    return $decl;
  }

  <<__MemoizeLSB>>
  final public static function __xhpReflectionChildrenDeclaration(
  ): ReflectionXHPChildrenDeclaration {
    return new ReflectionXHPChildrenDeclaration(
      :xhp::class2element(static::class),
      static::__legacySerializedXHPChildrenDeclaration(),
    );
  }

  final public static function __xhpReflectionCategoryDeclaration(
  ): keyset<string> {
    return Keyset\keys(self::emptyInstance()->__xhpCategoryDeclaration());
  }

  // Work-around to call methods that should be static without a real
  // instance.
  <<__MemoizeLSB>>
  private static function emptyInstance(): this {
    return (
      new \ReflectionClass(static::class)
    )->newInstanceWithoutConstructor();
  }

  final public function getAttributes(): dict<string, mixed> {
    return $this->attributes;
  }

  /**
   * Determines if a given XHP attribute "key" represents an XHP spread operator
   * in the constructor.
   */
  private static function isSpreadKey(string $key): bool {
    return substr($key, 0, strlen(:xhp::SPREAD_PREFIX)) === :xhp::SPREAD_PREFIX;
  }

  /**
   * Implements the XHP spread operator in expressions like:
   *   <foo attr1="bar" {...$xhp} />
   *
   * This will only copy defined attributes on $xhp to when they are also
   * defined on $this. "Special" data-/aria- attributes will still need to be
   * implicitly transferred, since the typechecker never knows about them.
   *
   * Defaults from $xhp are copied as well, if they are present.
   */
  protected final function spreadElementImpl(
    :x:composable_element $element,
  ): void {
    foreach ($element::__xhpReflectionAttributes() as $attr_name => $attr) {
      $our_attr = static::__xhpReflectionAttribute($attr_name);
      if ($our_attr === null) {
        continue;
      }

      $val = $element->getAttribute($attr_name);
      if ($val === null) {
        continue;
      }

      // If the receiving class has the same attribute and we had a value or
      // a default, then copy it over.
      $this->setAttribute($attr_name, $val);
    }
  }

  /**
   * Sets an attribute in this element's attribute store.
   *
   * @param $attr      attribute to set
   * @param $val       value
   */
  final public function setAttribute(string $attr, mixed $value): this {
    invariant(!$this->__isRendered, "Can't setAttribute after render");
    $this->attributes[$attr] = $value;
    return $this;
  }

  /**
   * Takes a KeyedContainer and adds each as an attribute.
   *
   * @param $attrs    KeyedContainer of attributes
   */
  final public function setAttributes(
    KeyedTraversable<string, mixed> $attrs,
  ): this {
    foreach ($attrs as $key => $value) {
      $this->setAttribute($key, $value);
    }
    return $this;
  }

  /**
   * Whether the attribute has been explicitly set to a nonnull value by the
   * caller (vs. using the default set by "attribute" in the class definition).
   *
   * @param $attr attribute to check
   */
  final public function isAttributeSet(string $attr): bool {
    return C\contains_key($this->attributes, $attr);
  }

  /**
   * Removes an attribute from this element's attribute store.
   *
   * @param $attr      attribute to remove
   */
  final public function removeAttribute(string $attr): this {
    invariant(!$this->__isRendered, "Can't removeAttribute after render");
    unset($this->attributes[$attr]);
    return $this;
  }

  /**
   * @deprecated This functionality will be removed in a future release.
   *
   * Sets an attribute in this element's attribute store. Always foregoes
   * validation.
   *
   * @param $attr      attribute to set
   * @param $val       value
   */
  final public function forceAttribute(string $attr, mixed $value): this {
    invariant(!$this->__isRendered, "Can't forceAttribute after render");
    $this->attributes[$attr] = $value;
    return $this;
  }
  /**
   * Returns all contexts currently set.
   *
   * @return           All contexts
   */
  final public function getAllContexts(): dict<string, mixed> {
    return $this->context;
  }

  /**
   * Returns a specific context value. Can include a default if not set.
   *
   * @param   $key     The context key
   * @param   $default The value to return if not set (optional)
   * @return           The context value or $default
   */
  final public function getContext(string $key, mixed $default = null): mixed {
    // You can't use ?? here, since the context may contain nulls.
    if (C\contains_key($this->context, $key)) {
      return $this->context[$key];
    }
    return $default;
  }

  /**
   * Sets a value that will be automatically passed down through a render chain
   * and can be referenced by children and composed elements. For instance, if
   * a root element sets a context of "admin_mode" = true, then all elements
   * that are rendered as children of that root element will receive this
   * context WHEN RENDERED. The context will not be available before render.
   *
   * @param $key       The key
   * @param $default   The value to set
   * @return           $this
   */
  final public function setContext(string $key, mixed $value): this {
    invariant(!$this->__isRendered, "Can't setContext after render");
    $this->context[$key] = $value;
    return $this;
  }

  /**
   * Sets a value that will be automatically passed down through a render chain
   * and can be referenced by children and composed elements. For instance, if
   * a root element sets a context of "admin_mode" = true, then all elements
   * that are rendered as children of that root element will receive this
   * context WHEN RENDERED. The context will not be available before render.
   *
   * @param KeyedContainer $context  A map of key/value pairs
   * @return               $this
   */
  final public function addContextMap(
    KeyedContainer<string, mixed> $context,
  ): this {
    invariant(!$this->__isRendered, "Can't setContext after render");
    $this->context = Dict\merge($this->context, $context);
    return $this;
  }

  /**
   * Transfers the context but will not overwrite anything. This is done only
   * for rendering because we don't want a parent's context to replace a
   * child's context if they have the same key.
   *
   * @param $parentContext  The context to transfer
   */
  final protected function __transferContext(
    KeyedContainer<string, mixed> $parentContext,
  ): void {
    foreach ($parentContext as $key => $value) {
      // You can't use ??= here, since context may contain nulls.
      if (!C\contains_key($this->context, $key)) {
        $this->context[$key] = $value;
      }
    }
  }

  abstract protected function __flushSubtree(): Awaitable<:x:primitive>;

  /**
   * Defined in elements by the `attribute` keyword. The declaration is simple.
   * There is a keyed array, with each key being an attribute. Each value is
   * an array with 4 elements. The first is the attribute type. The second is
   * meta-data about the attribute. The third is a default value (null for
   * none). And the fourth is whether or not this value is required.
   *
   * Attribute types are suggested by the TYPE_* constants.
   */
  protected static function __xhpAttributeDeclaration(
  ): darray<string, darray<int, mixed>> {
    return darray[];
  }

  /**
   * Defined in elements by the `category` keyword. This is just a list of all
   * categories an element belongs to. Each category is a key with value 1.
   */
  protected function __xhpCategoryDeclaration(): darray<string, int> {
    return darray[];
  }

  const int __NO_LEGACY_CHILDREN_DECLARATION = -31337;

  /**
   * Defined in elements by the `children` keyword. This returns a pattern of
   * allowed children. The return value is potentially very complicated. The
   * two simplest are 0 and 1 which mean no children and any children,
   * respectively. Otherwise you're dealing with an array which is just the
   * biggest mess you've ever seen.
   */
  protected function __xhpChildrenDeclaration(): mixed {
    return self::__NO_LEGACY_CHILDREN_DECLARATION;
  }

  /**
   * Validates that this element's children match its children descriptor, and
   * throws an exception if that's not the case.
   */
  protected function validateChildren(): void {
    $decl = self::__xhpReflectionChildrenDeclaration();
    $type = $decl->getType();
    if ($type === XHPChildrenDeclarationType::ANY_CHILDREN) {
      return;
    }
    if ($type === XHPChildrenDeclarationType::NO_CHILDREN) {
      if ($this->children) {
        throw new XHPInvalidChildrenException($this, 0);
      } else {
        return;
      }
    }
    list($ret, $ii) = $this->validateChildrenExpression(
      $decl->getExpression(),
      0,
    );
    if (!$ret || $ii < C\count($this->children)) {
      if (($this->children[$ii] ?? null) is XHPAlwaysValidChild) {
        return;
      }
      throw new XHPInvalidChildrenException($this, $ii);
    }
  }

  final private function validateChildrenExpression(
    ReflectionXHPChildrenExpression $expr,
    int $index,
  ): (bool, int) {
    switch ($expr->getType()) {
      case XHPChildrenExpressionType::SINGLE:
        // Exactly once -- :fb_thing
        return $this->validateChildrenRule($expr, $index);
      case XHPChildrenExpressionType::ANY_NUMBER:
        // Zero or more times -- :fb_thing*
        do {
          list($ret, $index) = $this->validateChildrenRule($expr, $index);
        } while ($ret);
        return tuple(true, $index);

      case XHPChildrenExpressionType::ZERO_OR_ONE:
        // Zero or one times -- :fb_thing?
        list($_, $index) = $this->validateChildrenRule($expr, $index);
        return tuple(true, $index);

      case XHPChildrenExpressionType::ONE_OR_MORE:
        // One or more times -- :fb_thing+
        list($ret, $index) = $this->validateChildrenRule($expr, $index);
        if (!$ret) {
          return tuple(false, $index);
        }
        do {
          list($ret, $index) = $this->validateChildrenRule($expr, $index);
        } while ($ret);
        return tuple(true, $index);

      case XHPChildrenExpressionType::SUB_EXPR_SEQUENCE:
        // Specific order -- :fb_thing, :fb_other_thing
        $oindex = $index;
        list($sub_expr_1, $sub_expr_2) = $expr->getSubExpressions();
        list($ret, $index) = $this->validateChildrenExpression(
          $sub_expr_1,
          $index,
        );
        if ($ret) {
          list($ret, $index) = $this->validateChildrenExpression(
            $sub_expr_2,
            $index,
          );
        }
        if ($ret) {
          return tuple(true, $index);
        }
        return tuple(false, $oindex);

      case XHPChildrenExpressionType::SUB_EXPR_DISJUNCTION:
        // Either or -- :fb_thing | :fb_other_thing
        $oindex = $index;
        list($sub_expr_1, $sub_expr_2) = $expr->getSubExpressions();
        list($ret, $index) = $this->validateChildrenExpression(
          $sub_expr_1,
          $index,
        );
        if (!$ret) {
          list($ret, $index) = $this->validateChildrenExpression(
            $sub_expr_2,
            $index,
          );
        }
        if ($ret) {
          return tuple(true, $index);
        }
        return tuple(false, $oindex);
    }
  }

  final private function validateChildrenRule(
    ReflectionXHPChildrenExpression $expr,
    int $index,
  ): (bool, int) {
    switch ($expr->getConstraintType()) {
      case XHPChildrenConstraintType::ANY:
        if (C\contains_key($this->children, $index)) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case XHPChildrenConstraintType::PCDATA:
        if (
          C\contains_key($this->children, $index) &&
          !($this->children[$index] is :xhp)
        ) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case XHPChildrenConstraintType::ELEMENT:
        $class = $expr->getConstraintString();
        if (
          C\contains_key($this->children, $index) &&
          is_a($this->children[$index], $class, true)
        ) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case XHPChildrenConstraintType::CATEGORY:
        if (
          !C\contains_key($this->children, $index) ||
          !($this->children[$index] is :xhp)
        ) {
          return tuple(false, $index);
        }
        $category = $expr->getConstraintString()
          |> Str\replace($$, '__', ':')
          |> Str\replace($$, '_', '-');
        $child = $this->children[$index];
        assert($child is :xhp);
        $categories = $child->__xhpCategoryDeclaration();
        if (($categories[$category] ?? 0) === 0) {
          return tuple(false, $index);
        }
        return tuple(true, $index + 1);

      case XHPChildrenConstraintType::SUB_EXPR:
        return $this->validateChildrenExpression(
          $expr->getSubExpression(),
          $index,
        );
    }
  }

  /**
   * Returns the human-readable `children` declaration as seen in this class's
   * source code.
   *
   * Keeping this wrapper around reflection, as it fits well with
   * __getChildrenDescription.
   */
  public function __getChildrenDeclaration(): string {
    return self::__xhpReflectionChildrenDeclaration()->__toString();
  }

  /**
   * Returns a description of the current children in this element. Maybe
   * something like this:
   * <div><span>foo</span>bar</div> ->
   * :span[%inline],pcdata
   */
  final public function __getChildrenDescription(): string {
    $desc = varray[];
    foreach ($this->children as $child) {
      if ($child is :xhp) {
        $tmp = ':'.:xhp::class2element(get_class($child));
        $categories = $child->__xhpCategoryDeclaration();
        if (C\count($categories) > 0) {
          $tmp .= '[%'.implode(',%', array_keys($categories)).']';
        }
        $desc[] = $tmp;
      } else {
        $desc[] = 'pcdata';
      }
    }
    return implode(',', $desc);
  }

  final public function categoryOf(string $c): bool {
    $categories = $this->__xhpCategoryDeclaration();
    if ($categories[$c] ?? null !== null) {
      return true;
    }
    // XHP parses the category string
    $c = str_replace(varray[':', '-'], varray['__', '_'], $c);
    return ($categories[$c] ?? null) !== null;
  }
}
