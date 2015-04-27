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

interface HasXHPHelpers extends HasXHPBaseHTMLHelpers, XHPHasTransferAttributes {
};

/*
 * Use of this trait assumes you have inherited attributes from an HTML element.
 * For the bare minimum, use:
 *
 * attribute :xhp:html-element;
 */
trait XHPHelpers implements HasXHPHelpers {
  require extends :x:composable-element;

  use XHPBaseHTMLHelpers;

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

  protected function getAttributeNamesThatAppendValuesOnTransfer(): ImmSet<string> {
    return ImmSet { 'class' };
  }

  final public function transferAttributesToRenderedRoot(
    :x:composable-element $root,
  ): void {
    if (:xhp::$ENABLE_VALIDATION && $root instanceof :x:element) {
      if (!($root instanceof HasXHPHelpers)) {
        throw new XHPClassException(
          $this,
          'render() must return an object using the XHPHelpers trait.'
        );
      }

      $rootID = $root->getAttribute('id') ?: null;
      $thisID = $this->getAttribute('id') ?: null;

      if ($rootID && $thisID && $rootID != $thisID) {
        throw new XHPException(
          'ID Collision. '.(:xhp::class2element(self::class)).' has an ID '.
          'of "'.$thisID.'" but it renders into a(n) '.
          (:xhp::class2element(get_class($root))).
          ' which has an ID of "'.$rootID.'". The latter will get '.
          'overwritten (most often unexpectedly). If you are intending for '.
          'this behavior consider calling $this->removeAttribute(\'id\') '.
          'before returning your node from compose().'
        );
      }
    }
    assert($root instanceof HasXHPHelpers);

    $attributes = $this->getAttributes();

    // We want to append classes to the root node, instead of replace them,
    // so do this attribute manually and then remove it.
    foreach ($this->getAttributeNamesThatAppendValuesOnTransfer() as $attr) {
      if (array_key_exists($attr, $attributes)) {
        $rootAttributes = $root->getAttributes();
        if (
          array_key_exists($attr, $rootAttributes)
          && ($rootValue = (string) $rootAttributes[$attr]) !== ''
        ) {
          $thisValue = (string) $attributes[$attr];
          if ($thisValue !== '') {
            $root->setAttribute($attr, $rootValue.' '.$thisValue);
          }
          $this->removeAttribute($attr);
        }
      }
    }

    // Transfer all valid attributes to the returned node.
    $this->transferAllAttributes($root);
  }
}
