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

interface HasXHPHelpers {
  require extends :x:composable-element;
};

/*
 * Use of this trait assumes you have inherited attributes from an HTML element.
 * For the bare minimum, use:
 *
 * attribute :xhp:html-element;
 */
trait XHPHelpers implements HasXHPHelpers {

  require extends :x:composable-element;

  /*
   * Appends a string to the "class" attribute (space separated).
   */
  public function addClass(string $class): this {
    try {
      $current_class = /* UNSAFE_EXPR */ $this->:class;
      return $this->setAttribute('class', trim($current_class.' '.$class));
    } catch (XHPInvalidAttributeException $error) {
      throw new XHPException(
        'You are trying to add an HTML class to a(n) '.
        :xhp::class2element(static::class).' element, but it does not support '.
        'the "class" attribute. The best way to do this is to inherit '.
        'the HTML attributes from the element your component will render into.',
      );
    }
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
    $id = /* UNSAFE_EXPR */ $this->:id;
    if ($id === null || $id === '') {
      try {
        $this->setAttribute('id', $id = substr(md5(mt_rand(0, 100000)), 0, 10));
      } catch (XHPInvalidAttributeException $error) {
        throw new XHPException(
          'You are trying to add an HTML id to a(n) '.
          :xhp::class2element(static::class).' element, but it does not '.
          'support the "id" attribute. The best way to do this is to inherit '.
          'the HTML attributes from the element your component will render '.
          'into.',
        );
      }
    }
    return (string)$id;
  }

  /*
   * Fetches the "id" attribute, will generate a unique value if not set.
   */
  final public function getID(): string {
    return $this->requireUniqueID();
  }

  /*
   * Copies all attributes that are set on $this and valid on $target to
   * $target.
   */
  final public function copyAllAttributes(
    :x:composable-element $target,
  ): void {
    $this->transferAttributesImpl($target, Set{});
  }

  /*
   * Copies only the non-HTML attributes that are set on $this and valid on
   * $target to $target.
   */
  final public function copyCustomAttributes(
    :x:composable-element $target,
  ): void {
    $this->transferAttributesImpl($target);
  }

  /*
   * Copies all attributes except those specified that are set on $this and
   * valid on $target to $target.
   */
  final public function copyAttributesExcept(
    :x:composable-element $target,
    Set<string> $ignore,
  ): void {
    $this->transferAttributesImpl($target, $ignore);
  }

  /*
   * Transfers all attributes that are set on $this and valid on $target to
   * $target. This will unset all transfered attributes from $this.
   */
  final public function transferAllAttributes(
    :x:composable-element $target,
  ): void {
    $this->transferAttributesImpl($target, Set{}, true);
  }

  /*
   * Transfers only the non-HTML attributes that are set on $this and valid on
   * $target to $target. This will unset all transfered attributes from $this.
   */
  final public function transferCustomAttributes(
    :x:composable-element $target,
  ): void {
    $this->transferAttributesImpl($target, null, true);
  }

  /*
   * Transfers all attributes except those specified that are set on $this and
   * valid on $target to $target. This will unset all transfered attributes from
   * $this.
   */
  final public function transferAttributesExcept(
    :x:composable-element $target,
    Set<string> $ignore,
  ): void {
    $this->transferAttributesImpl($target, $ignore, true);
  }

  /*
   * The grunt work of transfering attributes. Don't call this function
   * directly. Instead, use one of the transfer/copy flavors above.
   */
  final private function transferAttributesImpl(
    :x:composable-element $target,
    ?Set<string> $ignore = null,
    bool $remove = false,
  ): void {
    if ($ignore === null) {
      $ignore = :xhp:html-element::__xhpAttributeDeclaration();
    } else {
      $ignore = array_fill_keys($ignore->toArray(), true);
    }

    $compatible = new Map($target::__xhpAttributeDeclaration());
    $transferAttributes = array_diff_key($this->getAttributes(), $ignore);
    foreach ($transferAttributes as $attribute => $value) {
      if (
        $compatible->containsKey($attribute)
        || ReflectionXHPAttribute::IsSpecial($attribute)
      ) {
        try {
          $target->setAttribute($attribute, $value);
        } catch (XHPInvalidAttributeException $error) {
          // This only happens when an attribute name collision occurs but the
          // two have different data types or different possible enum values.
          // This can be dangerous because the result when validation is off
          // will be different than when validation is on, so you should fix
          // this by renaming one of the attributes.
          $target = get_class($target);
          throw new XHPException(
            :xhp::class2element(static::class).' and '.
            :xhp::class2element($target).' both support the "'.$attribute.'" '.
            'attribute, but they have different signatures. This is a '.
            'problem because the behavior when transfering or copying '.
            'attributes while validation is on will be different than while '.
            'validation is off. Rename the attribute on at least one of these '.
            'elements to fix this.',
          );
        }
        if ($remove) {
          $this->removeAttribute($attribute);
        }
      }
    }
  }

}
