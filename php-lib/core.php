<?hh

/*
  +----------------------------------------------------------------------+
  | XHP                                                                  |
  +----------------------------------------------------------------------+
  | Copyright (c) 2009 - 2013 Facebook, Inc. (http://www.facebook.com)   |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE.PHP, and is    |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
*/

abstract class :xhp implements XHPChild {
  abstract public function __construct(
    KeyedTraversable<string, mixed> $attributes,
    Traversable<XHPChild> $children,
  );
  abstract public function appendChild(mixed $child): this;
  abstract public function prependChild(mixed $child): this;
  abstract public function replaceChildren(...): this;
  abstract public function getChildren(?string $selector = null): Vector<XHPChild>;
  abstract public function getFirstChild(?string $selector = null): ?XHPChild;
  abstract public function getLastChild(?string $selector = null): ?XHPChild;
  abstract public function getAttribute(string $attr): mixed;
  abstract public function getAttributes(): Map<string, mixed>;
  abstract public function setAttribute(string $attr, mixed $val): this;
  abstract public function setAttributes(KeyedTraversable<string, mixed> $attrs): this;
  abstract public function isAttributeSet(string $attr): bool;
  abstract public function removeAttribute(string $attr): this;
  abstract public function categoryOf(string $cat): bool;
  abstract public function __toString(): string;
  abstract protected function &__xhpCategoryDeclaration(): array<string, int>;
  abstract protected function &__xhpChildrenDeclaration(): mixed;
  protected static function &__xhpAttributeDeclaration(): array<string, array<int, mixed>> {
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
  public static bool $ENABLE_VALIDATION = true;

  final protected static function renderChild(XHPChild $child): string {
    if ($child instanceof :xhp) {
      return $child->__toString();
    } else if (is_array($child)) {
      throw new XHPRenderArrayException('Can not render array!');
    } else {
      return htmlspecialchars((string)$child);
    }
  }

  public static function element2class(string $element): string {
    return 'xhp_'.str_replace(array(':', '-'), array('__', '_'), $element);
  }

  public static function class2element(string $class): string {
    return str_replace(array('__', '_'), array(':', '-'), preg_replace('#^xhp_#i', '', $class));
  }
}

/**
 * For backwards compatibility only -- this class really shouldn't exist. Use
 * :xhp or :x:composable-element as appropriate, but never :x:base.
 */
abstract class :x:base extends :xhp {}
abstract class :x:composable-element extends :x:base {
  private Map<string, mixed> $attributes = Map{};
  private Vector<XHPChild> $children = Vector{};
  private Map<string, mixed> $context = Map{};

  private static $specialAttributes = ImmSet {
    'data',
    'aria',
  };

  // Private constants indicating the declared types of attributes
  const int TYPE_STRING   = 1;
  const int TYPE_BOOL     = 2;
  const int TYPE_NUMBER   = 3;
  const int TYPE_ARRAY    = 4;
  const int TYPE_OBJECT   = 5;
  const int TYPE_VAR      = 6;
  const int TYPE_ENUM     = 7;
  const int TYPE_FLOAT    = 8;
  const int TYPE_CALLABLE = 9;

  protected function init(): void {}

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
  final public function __construct(KeyedTraversable<string, mixed> $attributes,
                                    Traversable<XHPChild> $children) {
    foreach ($children as $child) {
      $this->appendChild($child);
    }
    $this->setAttributes($attributes);
    if (:xhp::$ENABLE_VALIDATION) {
      // There is some cost to having defaulted unused arguments on a function
      // so we leave these out and get them with func_get_args().
      $args = func_get_args();
      if (isset($args[2])) {
        $this->source = "$args[2]:$args[3]";
      } else {
        $this->source =
          'You have ENABLE_VALIDATION on, but debug information is not being ' .
          'passed to XHP objects correctly. Ensure xhp.include_debug is on ' .
          'in your PHP configuration. Without this option enabled, ' .
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
    if ($child instanceof Traversable) {
      foreach ($child as $c) {
        $this->appendChild($c);
      }
    } else if ($child instanceof :x:frag) {
      $this->children->addAll($child->children);
    } else if ($child !== null) {
      assert($child instanceof XHPChild);
      $this->children->add($child);
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
  final public function replaceChildren(...): this {
    // This function has been micro-optimized
    $args = func_get_args();
    $new_children = Vector {};
    foreach ($args as $xhp) {
      if ($xhp) {
        if ($xhp instanceof :x:frag) {
          foreach ($xhp->children as $child) {
            $new_children->add($child);
          }
        } else if (!is_array($xhp)) {
          $new_children->add($xhp);
        } else {
          foreach ($xhp as $element) {
            if ($element instanceof :x:frag) {
              foreach ($element->children as $child) {
                $new_children->add($child);
              }
            } else if ($element !== null) {
              $new_children->add($element);
            }
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
  final public function getChildren(?string $selector = null): Vector<XHPChild> {
    if (!$selector) {
      return $this->children;
    }
    $result = Vector {};
    if ($selector[0] == '%') {
      $selector = substr($selector, 1);
      foreach ($this->children as $child) {
        if ($child instanceof :xhp && $child->categoryOf($selector)) {
          $result->add($child);
        }
      }
    } else {
      $selector = :xhp::element2class($selector);
      foreach ($this->children as $child) {
        if ($child instanceof $selector) {
          $result->add($child);
        }
      }
    }
    return $result;
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
    if (!$selector) {
      return $this->children->get(0);
    } else if ($selector[0] == '%') {
      $selector = substr($selector, 1);
      foreach ($this->children as $child) {
        if ($child instanceof :xhp && $child->categoryOf($selector)) {
          return $child;
        }
      }
    } else {
      $selector = :xhp::element2class($selector);
      foreach ($this->children as $child) {
        if ($child instanceof $selector) {
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
   * Returns true if the attribute is a data- or aria- attribute.
   *
   * @param $attr      attribute to fetch
   * @return           bool
   */
  final private static function isAttributeSpecial(string $attr): bool {
    // Must be at least 6 characters, with a '-' in the 5th position
    return
      isset($attr[5])
      && $attr[4] == '-'
      && self::$specialAttributes->contains(substr($attr, 0, 4));
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
  final public function getAttribute(string $attr) {
    // Return the attribute if it's there
    if ($this->attributes->containsKey($attr)) {
      return $this->attributes->get($attr);
    }

    if (!self::isAttributeSpecial($attr)) {
      // Get the declaration
      $decl = static::__xhpAttributeDeclaration();

      if (!isset($decl[$attr])) {
        throw new XHPAttributeNotSupportedException($this, $attr);
      } else if (!empty($decl[$attr][3])) {
        throw new XHPAttributeRequiredException($this, $attr);
      } else {
        return $decl[$attr][2];
      }
    } else {
      return null;
    }
  }

  final public function getAttributes(): Map<string, mixed> {
    return $this->attributes;
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
    if (!self::isAttributeSpecial($attr)) {
      $value = $this->validateAttributeValue($attr, $value);
    } else {
      $value = (string)$value;
    }
    $this->attributes->set($attr, $value);
    return $this;
  }

  /**
   * Takes an array of key/value pairs and adds each as an attribute.
   *
   * @param $attrs    array of attributes
   */
  final public function setAttributes(KeyedTraversable<string, mixed> $attrs): this {
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
    if (!self::isAttributeSpecial($attr)) {
      $value = $this->validateAttributeValue($attr, null);
    }
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
  final public function getAllContexts(): Map {
    return $this->context;
  }

  /**
   * Returns a specific context value. Can include a default if not set.
   *
   * @param string $key     The context key
   * @param mixed $default  The value to return if not set (optional)
   * @return mixed          The context value or $default
   */
  final public function getContext(string $key, ?mixed $default): mixed {
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
  final public function setContext(string $key, ?mixed $value): this {
    $this->context->set($key, $value);
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
    $this->context->add($context);
    return $this;
  }

  /**
   * Transfers the context but will not overwrite anything. This is done only
   * for rendering because we don't want a parent's context to replace a
   * child's context if they have the same key.
   *
   * @param array $parentContext  The context to transfer
   */
  final private function transferContext(Map<string, mixed> $parentContext): void {
    foreach ($parentContext as $key => $value) {
      if (!$this->context->containsKey($key)) {
        $this->context->set($key, $value);
      }
    }
  }

  final protected function __flushElementChildren(): void {
    // Flush all :xhp elements to x:primitive's
    $ln = count($this->children);
    for ($ii = 0; $ii < $ln; ++$ii) {
      $child = $this->children->get($ii);
      if ($child instanceof :x:composable-element) {
        $child->transferContext($this->context);
      }

      if ($child instanceof :x:element) {
        $child = $child->__flushRenderedRootElement();

        if ($child instanceof :x:frag) {
          $children = $this->children->toValuesArray();
          array_splice($children, $ii, 1, $child->children);
          $this->children = new Vector($children);
          $ln = count($this->children);
          --$ii;
        } else {
          $this->children->set($ii, $child);
        }
      }
    }
  }

  final protected function __flushRenderedRootElement(): :x:primitive {
    $that = $this;
    // Flush root elements returned from render() to an :x:primitive
    while (($composed = $that->render()) instanceof :x:element) {
      if (:xhp::$ENABLE_VALIDATION) {
        $composed->validateChildren();
      }
      $composed->transferContext($that->context);
      $that = $composed;
    }

    if ($composed instanceof :x:primitive) {
      $composed->transferContext($that->context);
    } else if (:xhp::$ENABLE_VALIDATION) {
      // render() must always return XHPPrimitives
      throw new XHPCoreRenderException($this, $that);
    }
    return $composed;
  }

  /**
   * Defined in elements by the `attribute` keyword. The declaration is simple.
   * There is a keyed array, with each key being an attribute. Each value is
   * an array with 4 elements. The first is the attribute type. The second is
   * meta-data about the attribute. The third is a default value (null for
   * none). And the fourth is whether or not this value is required.
   *
   * Attribute types are suggested by the TYPE_* constants.
   */
  protected static function &__xhpAttributeDeclaration(): array<string, array<int, mixed>> {
    static $_ = array();
    return $_;
  }

  /**
   * Defined in elements by the `category` keyword. This is just a list of all
   * categories an element belongs to. Each category is a key with value 1.
   */
  protected function &__xhpCategoryDeclaration(): array<string, int> {
    static $_ = array();
    return $_;
  }

  /**
   * Defined in elements by the `children` keyword. This returns a pattern of
   * allowed children. The return value is potentially very complicated. The
   * two simplest are 0 and 1 which mean no children and any children,
   * respectively. Otherwise you're dealing with an array which is just the
   * biggest mess you've ever seen.
   */
  protected function &__xhpChildrenDeclaration(): mixed {
    static $_ = 1;
    return $_;
  }

  /**
   * Throws an exception if $val is not a valid value for the attribute $attr
   * on this element.
   */
  final protected function validateAttributeValue<T>(string $attr, T $val): mixed {
    $decl = static::__xhpAttributeDeclaration();
    if (!isset($decl[$attr])) {
      throw new XHPAttributeNotSupportedException($this, $attr);
    }
    if ($val === null) {
      return null;
    }
    switch ((int)$decl[$attr][0]) {
      case self::TYPE_STRING:
        $val = (string)$val;
        break;

      case self::TYPE_BOOL:
        if (!is_bool($val)) {
          if ($val === "false") {
            $val = false;
          } else {
            $val = (bool)$val;
          }
        }
        break;

      case self::TYPE_NUMBER:
        if (!is_int($val)) {
          $val = (int)$val;
        }
        break;

      case self::TYPE_FLOAT:
        if (!is_numeric($val)) {
          $val = (float)$val;
        }
        break;

      case self::TYPE_CALLABLE:
        if (!is_callable($val)) {
          throw new XHPInvalidAttributeException($this, 'callable', $attr, $val);
        }
        break;

      case self::TYPE_ARRAY:
        if (!is_array($val)) {
          throw new XHPInvalidAttributeException($this, 'array', $attr, $val);
        }
        if ($decl[$attr][1]) {
          $this->validateArrayAttributeValue((array)$decl[$attr][1], $attr, $val);
        }
        break;

      case self::TYPE_OBJECT:
        if (!($val instanceof $decl[$attr][1])) {
          throw new XHPInvalidAttributeException(
            $this, (string)$decl[$attr][1], $attr, $val
          );
        }
        break;

      // case self::TYPE_VAR: `var` (any type)

      case self::TYPE_ENUM:
        $found = false;
        foreach ((array)$decl[$attr][1] as $enum) {
          if ($enum === $val) {
            $found = true;
            break;
          }
        }
        if (!$found) {
          $enums = 'enum("' . implode('","', (array)$decl[$attr][1]) . '")';
          throw new XHPInvalidAttributeException($this, $enums, $attr, $val);
        }
    }
    return $val;
  }

  final private function validateArrayAttributeValue(array<int, mixed> $decl, string $attr,
                                                     array<mixed> $val): void {
    if ($decl[0]) { // Key declaration
      if ($decl[0] == self::TYPE_STRING) {
        $type = 'string';
        $func = 'is_string';
      } else {
        $type = 'int';
        $func = 'is_int';
      }
      if (count($val) != count(array_filter(array_keys($val), $func))) {
        $bad = $type == 'string' ? 'int' : 'string';
        throw new XHPInvalidArrayKeyAttributeException(
          $this,
          (string)$type,
          $attr,
          $bad
        );
      }
    }
    switch ((int)$decl[1]) { // Value declaration
      case self::TYPE_STRING:
        $type = 'string';
        $func = 'is_string';
        break;
      case self::TYPE_BOOL:
        $type = 'bool';
        $func = 'is_bool';
        break;
      case self::TYPE_NUMBER:
        $type = 'int';
        $func = 'is_int';
        break;
      case self::TYPE_FLOAT:
        $type = 'float';
        $func = 'is_numeric';
        break;
      case self::TYPE_CALLABLE:
        $type = 'callable';
        $func = 'is_callable';
        return;
      case self::TYPE_ARRAY:
        $type = 'array';
        $func = 'is_array';
        break;
      case self::TYPE_OBJECT:
        $type = $decl[2];
        $func = function($item) use ($type) {
          return $item instanceof $type;
        };
        break;
    }
    $filtered = array_filter($val, $func);
    if (count($val) != count($filtered)) {
      $bad = array_diff($val, $filtered);
      throw new XHPInvalidArrayAttributeException(
        $this,
        (string)$type,
        $attr,
        reset($bad)
      );
    }

    if (isset($decl[2]) && $decl[1] == self::TYPE_ARRAY) {
      foreach ($val as $arrayVal) {
        $this->validateArrayAttributeValue((array)$decl[2], $attr, (array)$arrayVal);
      }
    }
  }

  /**
   * Validates that this element's children match its children descriptor, and
   * throws an exception if that's not the case.
   */
  final protected function validateChildren(): void {
    $decl = $this->__xhpChildrenDeclaration();
    if ($decl === 1) { // Any children allowed
      return;
    }
    if ($decl === 0) { // No children allowed
      if ($this->children) {
        throw new XHPInvalidChildrenException($this, 0);
      } else {
        return;
      }
    }
    list($ret, $ii) = $this->validateChildrenExpression((array)$decl, 0);
    if (!$ret || $ii < count($this->children)) {
      throw new XHPInvalidChildrenException($this, $ii);
    }
  }

  final private function validateChildrenExpression(array<int, mixed> $decl,
                                                    int $index): (bool, int) {
    switch ((int)$decl[0]) {
      case 0: // Exactly once -- :fb-thing
        return $this->validateChildrenRule((int)$decl[1], $decl[2], $index);

      case 1: // Zero or more times -- :fb-thing*
        do {
          list($ret, $index) = $this->validateChildrenRule((int)$decl[1], $decl[2], $index);
        } while ($ret);
        return tuple(true, $index);

      case 2: // Zero or one times -- :fb-thing?
        list($_, $index) = $this->validateChildrenRule((int)$decl[1], $decl[2], $index);
        return tuple(true, $index);

      case 3: // One or more times -- :fb-thing+
        list($ret, $index) = $this->validateChildrenRule((int)$decl[1], $decl[2], $index);
        if (!$ret) {
          return tuple(false, $index);
        }
        do {
          list($ret, $index) = $this->validateChildrenRule((int)$decl[1], $decl[2], $index);
        } while ($ret);
        return tuple(true, $index);

      case 4: // Specific order -- :fb-thing, :fb-other-thing
        $oindex = $index;
        list($ret, $index) = $this->validateChildrenExpression((array)$decl[1], $index);
        if ($ret) {
          list($ret, $index) = $this->validateChildrenExpression((array)$decl[2], $index);
        }
        if ($ret) {
          return tuple(true, $index);
        }
        return tuple(false, $oindex);

      case 5: // Either or -- :fb-thing | :fb-other-thing
        $oindex = $index;
        list($ret, $index) = $this->validateChildrenExpression((array)$decl[1], $index);
        if (!$ret) {
          list($ret, $index) = $this->validateChildrenExpression((array)$decl[2], $index);
        }
        if ($ret) {
          return tuple(true, $index);
        }
        return tuple(false, $oindex);
    }
  }

  final private function validateChildrenRule(int $type, mixed $rule, int $index): (bool, int) {
    switch ($type) {
      case 1: // any element -- any
        if ($this->children->containsKey($index)) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case 2: // pcdata -- pcdata
        if ($this->children->containsKey($index) &&
            !($this->children->get($index) instanceof :xhp)) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case 3: // specific element -- :fb-thing
        if ($this->children->containsKey($index) &&
            $this->children->get($index) instanceof $rule) {
          return tuple(true, $index + 1);
        }
        return tuple(false, $index);

      case 4: // element category -- %block
        if (!$this->children->containsKey($index) ||
            !($this->children->get($index) instanceof :xhp)) {
          return tuple(false, $index);
        }
        $child = $this->children->get($index);
        assert($child instanceof :xhp);
        $categories = $child->__xhpCategoryDeclaration();
        if (empty($categories[(string)$rule])) {
          return tuple(false, $index);
        }
        return tuple(true, $index + 1);

      case 5: // nested rule -- ((:fb-thing, :fb-other-thing)*, :fb:thing-footer)
        return $this->validateChildrenExpression((array)$rule, $index);
    }
  }

  /**
   * Returns the human-readable `children` declaration as seen in this class's
   * source code.
   */
  final public function __getChildrenDeclaration(): string {
    $decl = $this->__xhpChildrenDeclaration();
    if ($decl === 1) {
      return 'any';
    }
    if ($decl === 0) {
      return 'empty';
    }
    return $this->renderChildrenDeclaration((array)$decl);
  }

  final private function renderChildrenDeclaration(array $decl): string {
    switch ($decl[0]) {
      case 0:
        return $this->renderChildrenRule((int)$decl[1], $decl[2]);

      case 1:
        return $this->renderChildrenRule((int)$decl[1], $decl[2]) . '*';

      case 2:
        return $this->renderChildrenRule((int)$decl[1], $decl[2]) . '?';

      case 3:
        return $this->renderChildrenRule((int)$decl[1], $decl[2]) . '+';

      case 4:
        return $this->renderChildrenDeclaration($decl[1]) . ',' .
          $this->renderChildrenDeclaration($decl[2]);

      case 5:
        return $this->renderChildrenDeclaration($decl[1]) . '|' .
          $this->renderChildrenDeclaration($decl[2]);
    }
  }

  final private function renderChildrenRule(int $type, mixed $rule): string {
    switch ($type) {
      case 1:
        return 'any';

      case 2:
        return 'pcdata';

      case 3:
        return ':' . :xhp::class2element((string)$rule);

      case 4:
        return '%' . (string)$rule;

      case 5:
        return '(' . $this->renderChildrenDeclaration((array)$rule) . ')';
    }
  }

  /**
   * Returns a description of the current children in this element. Maybe
   * something like this:
   * <div><span>foo</span>bar</div> ->
   * :span[%inline],pcdata
   */
  final public function __getChildrenDescription(): string {
    $desc = array();
    foreach ($this->children as $child) {
      if ($child instanceof :xhp) {
        $tmp = ':' . :xhp::class2element(get_class($child));
        if ($categories = $child->__xhpCategoryDeclaration()) {
          $tmp .= '[%'. implode(',%', array_keys($categories)) . ']';
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
    if (isset($categories[$c])) {
      return true;
    }
    // XHP parses the category string
    $c = str_replace(array(':', '-'), array('__', '_'), $c);
    return isset($categories[$c]);
  }
}

/**
 * :x:primitive lays down the foundation for very low-level elements. You
 * should directly :x:primitive only if you are creating a core element that
 * needs to directly implement stringify(). All other elements should subclass
 * from :x:element.
 */
abstract class :x:primitive extends :x:composable-element {
  abstract protected function stringify(): string;

  final public function __toString(): string {
    try {
      // Validate our children
      $this->__flushElementChildren();
      if (:xhp::$ENABLE_VALIDATION) {
        $this->validateChildren();
      }
    } catch (Exception $error) {
      trigger_error($error->getMessage(), E_USER_ERROR);
    }
    // Render to string
    return $this->stringify();
  }
}

/**
 * :x:element defines an interface that all user-land elements should subclass
 * from. The main difference between :x:element and :x:primitive is that
 * subclasses of :x:element should implement `render()` instead of `stringify`.
 * This is important because most elements should not be dealing with strings
 * of markup.
 */
abstract class :x:element extends :x:composable-element {
  final public function __toString(): string {
    $that = $this;

    try {
      if (:xhp::$ENABLE_VALIDATION) {
        $that->validateChildren();
      }
      $that = $that->__flushRenderedRootElement();
    } catch (Exception $error) {
      var_log($error->getTrace());
      trigger_error($error->getMessage(), E_USER_ERROR);
    }
    return $that->__toString();
  }
}

/**
 * An <x:frag /> is a transparent wrapper around any number of elements. When
 * you render it just the children will be rendered. When you append it to an
 * element the <x:frag /> will disappear and each child will be sequentially
 * appended to the element.
 */
class :x:frag extends :x:primitive {
  protected function stringify(): string {
    $buf = '';
    foreach ($this->getChildren() as $child) {
      $buf .= :xhp::renderChild($child);
    }
    return $buf;
  }
}

/**
 * Exceptions are neat.
 */
class XHPException extends Exception {
  protected static function getElementName(:xhp $that): string {
    $name = get_class($that);
    if (substr($name, 0, 4) !== 'xhp_') {
      return $name;
    } else {
      return :xhp::class2element($name);
    }
  }
}

class XHPClassException extends XHPException {
  public function __construct(:xhp $that, string $msg) {
    parent::__construct(
      'Exception in class `' . XHPException::getElementName($that) . "`\n\n".
      "$that->source\n\n".
      $msg
    );
  }
}

class XHPCoreRenderException extends XHPException {
  public function __construct(:xhp $that, mixed $rend) {
    parent::__construct(
      ':x:element::render must reduce an object to an :x:primitive, but `'.
      :xhp::class2element(get_class($that)).'` reduced into `'.gettype($rend)."`.\n\n".
      $that->source
    );
  }
}

class XHPRenderArrayException extends XHPException {
}

class XHPInvalidArrayAttributeException extends XHPException {
  public function __construct(:xhp $that, string $type, string $attr, mixed $val) {
    if (is_object($val)) {
      $val_type = get_class($val);
    } else {
      $val_type = gettype($val);
    }
    parent::__construct(
      "Invalid attribute `$attr` of type array<`$val_type`> supplied to element `".
      :xhp::class2element(get_class($that))."`, expected array<`$type`>.\n\n".
      $that->source
    );
  }
}

class XHPInvalidArrayKeyAttributeException extends XHPException {
  public function __construct(:xhp $that, string $type, string $attr, string $val_type) {
    parent::__construct(
      "Invalid key in attribute `$attr` of type array<$val_type => ?> supplied to element `".
      :xhp::class2element(get_class($that))."`, expected array<$type => ?>.\n\n".
      $that->source
    );
  }
}

class XHPAttributeNotSupportedException extends XHPException {
  public function __construct(:xhp $that, string $attr) {
    parent::__construct(
      'Attribute "'.$attr.'" is not supported in class '.
      '"'.XHPException::getElementName($that).'"'.
      "\n\n".$that->source."\n\n".
      'Please check for typos in your attribute. If you are creating a new '.
      'attribute on this element define it with the "attribute" keyword'."\n\n"
    );
  }
}

class XHPAttributeRequiredException extends XHPException {
  public function __construct(:xhp $that, string $attr) {
    parent::__construct(
      'Required attribute `'.$attr.'` was not specified in element '.
      '`'.XHPException::getElementName($that)."`.\n\n".
      $that->source
    );
  }
}

class XHPInvalidAttributeException extends XHPException {
  public function __construct(:xhp $that, string $type, string $attr, mixed $val) {
    if (is_object($val)) {
      $val_type = get_class($val);
    } else {
      $val_type = gettype($val);
    }
    parent::__construct(
      "Invalid attribute `$attr` of type `$val_type` supplied to element `".
      :xhp::class2element(get_class($that))."`, expected `$type`.\n\n".
      $that->source
    );
  }
}

class XHPInvalidChildrenException extends XHPException {
  public function __construct(object $that, int $index) {
    parent::__construct(
      'Element `'.XHPException::getElementName($that).'` was rendered with '.
      "invalid children.\n\n".
      "$that->source\n\n".
      "Verified $index children before failing.\n\n".
      "Children expected:\n".$that->__getChildrenDeclaration()."\n\n".
      "Children received:\n".$that->__getChildrenDescription()
    );
  }
}
