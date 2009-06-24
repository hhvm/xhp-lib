<?php

/**
 * XHPPrimitive lays down the foundation for very low-level XHP objects. You
 * should directly extend XHPPrimitive only if you are creating a core that
 * needs to directly implement __toString(). All other XHP objects should
 * subclass from XHPCore.
 */
abstract class XHPPrimitive {
  protected
    $attributes, // these will both be arrays
    $children;

  abstract protected function render();
  abstract public function __toString();
  protected function init() {}

  /**
   * __construct is called in response to an XHP element creation. Both
   * parameters will always be arrays.
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
  public final function __construct($attributes, $children) {
    if (IS_DEV_SITE) {
      foreach ($attributes as $key => $val) {
        $this->checkSupportedAttribute($key);
      }
    }
    $this->attributes = $attributes;
    foreach ($children as $child) {
      $this->appendChild($child);
    }
    $this->init();
  }

  /**
   * Returns an array of rendered children. You can optionally supply a glue
   * which will be inserted in between the returned elements.
   *
   * @param $glue    value to put in between each child
   * @return         array of children
   * TODO: I don't think we even need this function. We should just have a
   *       function that's like getChildren($glue), because they'll be rendered
   *       later anyway.
   */
  public function renderChildren($glue = null) {
    $childs = array();
    foreach ($this->children as $key => $child) {
      $childs[] = $child->render();
      if ($glue !== null) {
        $childs[] = $glue;
      }
    }
    if ($glue !== null) {
      array_pop($childs);
    }
    return $childs;
  }
  
  public function replaceChildren(/* ... */) {
    $args = func_get_args();
    $this->children = array();
    foreach ($args as $k => $children) {
      if (!is_array($children)) {
        $args[$k] = array($children);
      }
    }
    $this->children = call_user_func_array('array_merge', $args);
  }

  /**
   * Adds a child to the end of this node. If you give an array to this method
   * then it will behave like a DocumentFragment.
   *
   * @param $child     single child or array of children
   */
  public function appendChild($child) {
    if (is_array($child)) {
      $this->children = array_merge($this->children, $child);
    } else {
      $this->children[] = $child;
    }
  }

  /**
   * Throws an exception if a given attribute is not supported by this class.
   * This is called internally by setAttribute and getAttribute. This will only
   * be called in dev to ensure type safety.
   *
   * @param $attr     attribute to check
   */
  private final function checkSupportedAttribute($attr) {
    if (!in_array($attr, $this->supportedAttributes())) {
      throw new XHPAttributeNotSupportedException($this, $attr);
    }
  }

  /**
   * Fetches an attribute from this elements attribute store. If $attr is not
   * defined in the store, and $default is null an exception will be thrown. An
   * exception will also be thrown if $attr is not supported -- see
   * `supportedAttributes`
   *
   * @param $attr      attribute to fetch
   * @param $default   default value to return if attribute does not exist
   * @return           value
   */
  public function getAttribute($attr, $default = null) {
    if (IS_DEV_SITE) {
      $this->checkSupportedAttribute($attr);
    }

    // Return attribute if it's there, otherwise default or exception.
    if (isset($this->attributes[$attr])) {
      return $this->attributes[$attr];
    } else if ($default !== null) {
      return $default;
    } else {
      throw new XHPAttributeRequiredException($this, $attr);
    }
  }

  /**
   * Sets an attribute in this element's attribute store. An exception will be
   * thrown if $attr is not supported -- see `supportedAttributes`.
   *
   * @param $attr      attribute to set
   * @param $val       value
   */
  public function setAttribute($attr, $val) {
    if (IS_DEV_SITE) {
      $this->checkSupportedAttribute($attr);
    }
    $this->attributes[$attr] = $val;
  }

  /**
   * Returns an array of attributes that can be set on this element. Note that
   * this is only called in dev. If you attempt to touch an attribute not
   * specified an exception will be thrown.
   *
   * Note: When you override this function you will want to return an
   *       array_merge with parent::supportedAttributes();
   *
   * @return    array of supported attributes.
   */
  protected function supportedAttributes() {
    return array();
  }
}

/**
 * XHPCore defines an interface that all user-land XHP elements should subclass
 * from. The only difference between XHPCore and XHPPrimitive is that subclasses
 * of XHPCore are not allowed to implement `__toString`.
 */
abstract class XHPCore extends XHPPrimitive {
  public final function __toString() {
    $that = $this;
    while (($that = $that->render()) instanceof XHPCore);
    return $that->__toString();
  }
}

/**
 * XHPComposite is an idiomatic class in XHP which allows you to pass around
 * a node that acts an another node, and any `appendChild()` calls will append
 * to one of it's children.
 *
 * This can be useful if you want to pass around an object that will later be
 * wrapped on the inside.
 *
 * For instance, you can define an XHPComposite like this:
 * $parent = <div><p>{$anchor = <span />}</p></div>;
 * $composite = new XHPComposite($parent, $anchor);
 *
 * Then if another client wants to wrap the contents of your composite node,
 * he would do so by:
 * $composite->appendChild($anchor = <b />);
 * $composite = new XHPComposite($composite, $anchor);
 *
 * Note that we create another composite from the old one so that later down the
 * line we can wrap again with another tag.
 *
 * TODO: It would be nice if this was a subclass of XHPPrimitive
 */
class XHPComposite {
  protected
    $parent,
    $anchor;

  public function __construct($parent, $anchor) {
    $this->parent = $parent;
    $this->anchor = $anchor;
  }
  
  public function setAttribute($attr, $val) {
    $this->parent->setAttribute($attr, $val);
  }
  
  public function getAttribute($attr) {
    return $this->parent->getAttribute($attr, $val);
  }
  
  public function appendChild($child) {
    $this->anchor->appendChild($child);
  }
  
  public function __toString() {
    return $this->parent->__toString();
  }
}

/**
 * The JavascriptExpression and JavascriptConstructor interfaces are used to
 * specify that your element knows how to export itself to Javascript via
 * `jsprintf`.
 *
 * When you pass an object that implements either one of these interfaces to
 * `jsprintf` with the "%C" decorator your `js` method will be called to get
 * a string of Javascript. This will then be delivered to the browser.
 *
 * The distinction between JavascriptExpression and JavascriptConstructor is
 * important. Calls to JavascriptConstructor will be memoized per-instance in
 * Javascript. This is important if your Javascript has some kind of side-effect
 * (i.e. "new Controller()"). Elements that implement JavascriptExpression will
 * not be memoized. This would be used if your constructor has no side-effects,
 * (i.e. "$(%s)").
 */
interface JavascriptExpression {
  public function js();
}

interface JavascriptConstructor {
  public function js();
}

/**
 * Exceptions are neat.
 */
class XHPException extends Exception {
  protected static function getElementName($that) {
    $name = get_class($that);
    if (substr($name, 0, 4) !== 'xhp_') {
      return $name;
    } else {
      $name = substr($name, 4); // remove "xhp_"
      $name = str_replace(array('__', '_'), array(':', '-'), $name);
      return $name;
    }
  }
}

class XHPAttributeNotSupportedException extends XHPException {
  public function __construct($that, $attr) {
    parent::__construct(
      'Attribute `'.$attr.'` is not supported in class '.
      '`'.XHPException::getElementName($that).'`. Please check for typos in '.
      'your attribute. If you are creating a new attribute on this element '.
      'please add your attribute to the `supportedAttributes` method.'
    );
  }
}

class XHPAttributeRequiredException extends XHPException {
  public function __construct($that, $attr) {
    parent::__construct(
      'Required attribute `'.$attr.'` was not specified in element '.
      '`'.XHPException::getElementName($that).'`.'
    );
  }
}
