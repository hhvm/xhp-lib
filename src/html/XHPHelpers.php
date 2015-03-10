<?hh // strict
/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/*
 * Use of this trait assumes you have inherited attributes from an HTML element.
 * For the bare minimum, use:
 *
 * attribute :xhp:html-element;
 */
trait XHPHelpers {

  require extends :x:composable-element;

  /*
   * Appends a string to the "class" attribute (space separated).
   */
  public function addClass(string $class): this {
    return $this->setAttribute('class', trim($this->:class.' '.$class));
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
    $id = $this->:id;
    if ($id === null || $id === '') {
      $this->setAttribute('id', $id = substr(md5(mt_rand(0, 100000)), 0, 10));
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
  final public static function copyAllAttributes(
    :xhp $target,
  ): void {
    $this->transferAttributesImpl($target, Set{});
  }

  /*
   * Copies only the non-HTML attributes that are set on $this and valid on
   * $target to $target.
   */
  final public static function copyCustomAttributes(
    :xhp $target,
  ): void {
    $this->transferAttributesImpl($target);
  }

  /*
   * Copies all attributes except those specified that are set on $this and
   * valid on $target to $target.
   */
  final public static function copyAttributesExcept(
    :xhp $target,
    Set<string> $ignore,
  ): void {
    $this->transferAttributesImpl($target, $ignore);
  }

  /*
   * Transfers all attributes that are set on $this and valid on $target to
   * $target. This will unset all transfered attributes from $this.
   */
  final public static function transferAllAttributes(
    :xhp $target,
  ): void {
    $this->transferAttributesImpl($target, Set{}, true);
  }

  /*
   * Transfers only the non-HTML attributes that are set on $this and valid on
   * $target to $target. This will unset all transfered attributes from $this.
   */
  final public static function transferCustomAttributes(
    :xhp $target,
  ): void {
    $this->transferAttributesImpl($target, null, true);
  }

  /*
   * Transfers all attributes except those specified that are set on $this and
   * valid on $target to $target. This will unset all transfered attributes from
   * $this.
   */
  final public static function transferAttributesExcept(
    :xhp $target,
    Set<string> $ignore,
  ): void {
    $this->transferAttributesImpl($target, $ignore, true);
  }

  /*
   * The grunt work of transfering attributes. Don't call this function
   * directly. Instead, use one of the transfer/copy flavors above.
   */
  final private function transferAttributesImpl(
    :xhp $target,
    ?Set<string> $ignore = null,
    bool $remove = false,
  ): void {
    if ($ignore === null) {
      $ignore = :xhp:html-element::__xhpAttributeDeclaration();
    } else {
      $ignore = array_fill_keys($ignore->toArray(), true);
    }

    $compatible = $target->__xhpAttributeDeclaration();
    $transferAttributes = array_diff_key($this->getAttributes(), $ignore);
    foreach ($transferAttributes as $attribute => $value) {
      if (isset($compatible[$attribute])
          || ReflectionXHPAttribute::IsSpecial($attribute)) {
        $target->setAttribute($attribute, $value);
        if ($remove) {
          $this->removeAttribute($attribute);
        }
      }
    }
  }

}
