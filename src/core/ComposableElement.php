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
use namespace HH\Lib\{C, Str};

abstract class :x:composable-element extends :xhp {
  private Map<string, mixed> $attributes = Map {};
  private Vector<XHPChild> $children = Vector {};
  private Map<string, mixed> $context = Map {};

  protected function init(): void {
  }

  /**
   * A new :x:composable-element is instantiated for every literal tag
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
   */
  final public function __construct(
    KeyedTraversable<string, mixed> $attributes,
    Traversable<?XHPChild> $children,
    dynamic ...$debug_info
  ) {
    parent::__construct($attributes, $children);
    foreach ($children as $child) {
      $this->appendChild($child);
    }

    foreach ($attributes as $key => $value) {
      if (self::isSpreadKey($key)) {
        invariant(
          $value is :x:composable-element,
          "Only XHP can be used with an attribute spread operator",
        );
        $this->spreadElementImpl($value);
      } else {
        $this->setAttribute($key, $value);
      }
    }

    if (:xhp::isChildValidationEnabled()) {
      // There is some cost to having defaulted unused arguments on a function
      // so we leave these out and get them with func_get_args().
      if (C\count($debug_info) >= 2) {
        $this->source = (string)$debug_info[0].':'.(string)$debug_info[1];
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
   * Adds a child to the end of this node. If you give an array to this method
   * then it will behave like a DocumentFragment.
   *
   * @param $child     single child or array of children
   */
  final public function appendChild(mixed $child): this {
    if ($child is Traversable<_>) {
      foreach ($child as $c) {
        $this->appendChild($c);
      }
    } else if ($child is :x:frag) {
      $this->children->addAll($child->getChildren());
    } else if ($child !== null) {
      $this->children->add($child as XHPChild);
    }
    return $this;
  }

  /**
   * Adds a child to the beginning of this node. If you give an array to this
   * method then it will behave like a DocumentFragment.
   *
   * @param $child     single child or array of children
   */
  final public function prependChild(mixed $child): this {
    // There's no prepend to a Vector, so reverse, append, and reverse agains
    $this->children->reverse();
    $this->appendChild($child);
    $this->children->reverse();
    return $this;
  }

  /**
   * Replaces all children in this node. You may pass a single array or
   * multiple parameters.
   *
   * @param $children  Single child or array of children
   */
  final public function replaceChildren(mixed ...$children): this {
    // This function has been micro-optimized
    $new_children = Vector {};
    foreach ($children as $xhp) {
      /* HH_FIXME[4273] bogus "XHPChild always truthy" - FB T41388073 */
      if ($xhp is :x:frag) {
        foreach ($xhp->children as $child) {
          $new_children->add($child);
        }
      } else if (!($xhp is Traversable<_>)) {
        $new_children->add($xhp as XHPChild);
      } else {
        foreach ($xhp as $element) {
          if ($element is :x:frag) {
            foreach ($element->children as $child) {
              $new_children->add($child);
            }
          } else if ($element !== null) {
            $new_children->add($element as XHPChild);
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
   * @return array
   */
  final public function getChildren(
    ?string $selector = null,
  ): Vector<XHPChild> {
    if ($selector is string && $selector !== '') {
      $children = Vector {};
      if ($selector[0] == '%') {
        $selector = substr($selector, 1);
        foreach ($this->children as $child) {
          if ($child is :xhp && $child->categoryOf($selector)) {
            $children->add($child);
          }
        }
      } else {
        $selector = :xhp::element2class($selector);
        foreach ($this->children as $child) {
          if (is_a($child, $selector, /* allow strings = */ true)) {
            $children->add($child);
          }
        }
      }
    } else {
      $children = new Vector($this->children);
    }
    return $children;
  }


  /**
   * Fetches the first direct child of the element, or the first child that
   * matches the tag if one is given
   *
   * @param $selector   string   tag name or category (optional)
   * @return            element  the first child node (with the given selector),
   *                             false if there are no (matching) children
   */
  final public function getFirstChild(?string $selector = null): ?XHPChild {
    if ($selector === null) {
      return $this->children->get(0);
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
   * @param $selector  string   tag name or category (optional)
   * @return           element  the last child node (with the given selector),
   *                            false if there are no (matching) children
   */
  final public function getLastChild(?string $selector = null): ?XHPChild {
    $temp = $this->getChildren($selector);
    if ($temp->count() > 0) {
      $count = $temp->count();
      return $temp->at($count - 1);
    }
    return null;
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
    if ($this->attributes->containsKey($attr)) {
      return $this->attributes->get($attr);
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
    $map = static::__xhpReflectionAttributes();
    if ($map->containsKey($attr)) {
      return $map[$attr];
    }
    return null;
  }

  <<__MemoizeLSB>>
  final public static function __xhpReflectionAttributes(
  ): Map<string, ReflectionXHPAttribute> {
    $map = Map {};
    $decl = static::__xhpAttributeDeclaration();
    foreach ($decl as $name => $attr_decl) {
      $map[$name] = new ReflectionXHPAttribute($name, $attr_decl);
    }
    return $map;
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
  ): Set<string> {
    return new Set(
      \array_keys(self::emptyInstance()->__xhpCategoryDeclaration()),
    );
  }

  // Work-around to call methods that should be static without a real
  // instance.
  <<__MemoizeLSB>>
  private static function emptyInstance(): this {
    return (
      new \ReflectionClass(static::class)
    )->newInstanceWithoutConstructor();
  }

  final public function getAttributes(): Map<string, mixed> {
    return $this->attributes->toMap();
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
    :x:composable-element $element,
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
   * Sets an attribute in this element's attribute store. If the attribute is
   * not defined in the store and is not a data- or aria- attribute an
   * exception will be thrown. An exception will also be thrown if the
   * attribute value is invalid.
   *
   * @param $attr      attribute to set
   * @param $val       value
   */
  final public function setAttribute(string $attr, mixed $value): this {
    if (:xhp::isAttributeValidationEnabled()) {
      if (!ReflectionXHPAttribute::IsSpecial($attr)) {
        $value = $this->validateEnumValuesAndCoerceScalars($attr, $value);
      }
    }
    $this->attributes[$attr] = $value;
    return $this;
  }

  /**
   * Takes an array of key/value pairs and adds each as an attribute.
   *
   * @param $attrs    array of attributes
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
   * Whether the attribute has been explicitly set to a non-null value by the
   * caller (vs. using the default set by "attribute" in the class definition).
   *
   * @param $attr attribute to check
   */
  final public function isAttributeSet(string $attr): bool {
    return $this->attributes->containsKey($attr);
  }

  /**
   * Removes an attribute from this element's attribute store. An exception
   * will be thrown if $attr is not supported.
   *
   * @param $attr      attribute to remove
   * @param $val       value
   */
  final public function removeAttribute(string $attr): this {
    $this->attributes->removeKey($attr);
    return $this;
  }

  /**
   * Sets an attribute in this element's attribute store. Always foregoes
   * validation.
   *
   * @param $attr      attribute to set
   * @param $val       value
   */
  final public function forceAttribute(string $attr, mixed $value): this {
    $this->attributes->set($attr, $value);
    return $this;
  }
  /**
   * Returns all contexts currently set.
   *
   * @return array  All contexts
   */
  final public function getAllContexts(): Map<string, mixed> {
    return $this->context->toMap();
  }

  /**
   * Returns a specific context value. Can include a default if not set.
   *
   * @param string $key     The context key
   * @param mixed $default  The value to return if not set (optional)
   * @return mixed          The context value or $default
   */
  final public function getContext(string $key, mixed $default = null): mixed {
    if ($this->context->containsKey($key)) {
      return $this->context->get($key);
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
   * @param mixed $key      Either a key, or an array of key/value pairs
   * @param mixed $default  if $key is a string, the value to set
   * @return :xhp           $this
   */
  final public function setContext(string $key, mixed $value): this {
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
   * @param Map $context  A map of key/value pairs
   * @return :xhp         $this
   */
  final public function addContextMap(Map<string, mixed> $context): this {
    $this->context->setAll($context);
    return $this;
  }

  /**
   * Transfers the context but will not overwrite anything. This is done only
   * for rendering because we don't want a parent's context to replace a
   * child's context if they have the same key.
   *
   * @param array $parentContext  The context to transfer
   */
  final protected function __transferContext(
    Map<string, mixed> $parentContext,
  ): void {
    foreach ($parentContext as $key => $value) {
      if (!$this->context->containsKey($key)) {
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
  ): darray<string, varray<mixed>> {
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
   * Throws an exception if $val is not a valid value for the attribute $attr
   * on this element and this type appears to be an enum.
   * If this type is a scalar however, we will coerce it to that type.
   * This is something from the past and should ideally not be relied upon.
   * The fact that :xhp::enableAttributeValidation() enables these coercions
   * is misleading.
   */
  final protected function validateEnumValuesAndCoerceScalars(
    string $attr,
    mixed $val,
  ): mixed {
    if ($val is null) {
      return null;
    }
    $decl = static::__xhpReflectionAttribute($attr);
    if ($decl is null) {
      throw new XHPAttributeNotSupportedException($this, $attr);
    }

    switch ($decl->getValueType()) {
      case XHPAttributeType::TYPE_OBJECT:
        $class = $decl->getValueClass();
        if (enum_exists($class)) {
          /* HH_FIXME[4026] $class as enumname<_> */
          if (!$class::isValid($val)) {
            throw new XHPInvalidAttributeException($this, $class, $attr, $val);
          }
        }
        break;
      case XHPAttributeType::TYPE_ENUM:
        if (!(($val is string) && $decl->getEnumValues()->contains($val))) {
          $enums = 'enum("'.Str\join($decl->getEnumValues(), '","').'")';
          throw new XHPInvalidAttributeException($this, $enums, $attr, $val);
        }
        break;

      // Coercion should ideally not be relied on, but it is not causing trouble (yet)
      case XHPAttributeType::TYPE_STRING:
        if (!($val is string)) {
          $val = XHPAttributeCoercion::CoerceToString($this, $attr, $val);
        }
        break;

      case XHPAttributeType::TYPE_BOOL:
        if (!($val is bool)) {
          $val = XHPAttributeCoercion::CoerceToBool($this, $attr, $val);
        }
        break;

      case XHPAttributeType::TYPE_INTEGER:
        if (!($val is int)) {
          $val = XHPAttributeCoercion::CoerceToInt($this, $attr, $val);
        }
        break;

      case XHPAttributeType::TYPE_FLOAT:
        if (!($val is float)) {
          $val = XHPAttributeCoercion::CoerceToFloat($this, $attr, $val);
        }
        break;
      default:
        return $val;
    }
    return $val;
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
    if (!$ret || $ii < count($this->children)) {
      if (($this->children[$ii] ?? null) is XHPAlwaysValidChild) {
        return;
      }
      throw new XHPInvalidChildrenException($this, $ii);
    }
  }

  private function validateChildrenExpression(
    ReflectionXHPChildrenExpression $expr,
    int $index,
  ): (bool, int) {
    switch ($expr->getType()) {
      case XHPChildrenExpressionType::SINGLE:
        // Exactly once -- :fb-thing
        return $this->validateChildrenRule($expr, $index);
      case XHPChildrenExpressionType::ANY_NUMBER:
        // Zero or more times -- :fb-thing*
        do {
          list($ret, $index) = $this->validateChildrenRule($expr, $index);
        } while ($ret);
        return tuple(true, $index);

      case XHPChildrenExpressionType::ZERO_OR_ONE:
        // Zero or one times -- :fb-thing?
        list($_, $index) = $this->validateChildrenRule($expr, $index);
        return tuple(true, $index);

      case XHPChildrenExpressionType::ONE_OR_MORE:
        // One or more times -- :fb-thing+
        list($ret, $index) = $this->validateChildrenRule($expr, $index);
        if (!$ret) {
          return tuple(false, $index);
        }
        do {
          list($ret, $index) = $this->validateChildrenRule($expr, $index);
        } while ($ret);
        return tuple(true, $index);

      case XHPChildrenExpressionType::SUB_EXPR_SEQUENCE:
        // Specific order -- :fb-thing, :fb-other-thing
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
        // Either or -- :fb-thing | :fb-other-thing
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

  private function validateChildrenRule(
    ReflectionXHPChildrenExpression $expr,
    int $index,
  ): (bool, int) {
    switch ($expr->getConstraintType()) {
      case XHPChildrenConstraintType::ANY:
        if ($this->children->containsKey($index)) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case XHPChildrenConstraintType::PCDATA:
        if (
          $this->children->containsKey($index) &&
          !($this->children->get($index) is :xhp)
        ) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case XHPChildrenConstraintType::ELEMENT:
        $class = $expr->getConstraintString();
        if (
          $this->children->containsKey($index) &&
          is_a($this->children->get($index), $class, true)
        ) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case XHPChildrenConstraintType::CATEGORY:
        if (!$this->children->containsKey($index)) {
          return tuple(false, $index);
        }
        $child = $this->children->get($index);
        if (!$child is :xhp) {
          return tuple(false, $index);
        }
        $category = $expr->getConstraintString()
          |> Str\replace($$, '__', ':')
          |> Str\replace($$, '_', '-');
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
