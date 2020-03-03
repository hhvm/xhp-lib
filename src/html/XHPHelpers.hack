/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\_Private;
use namespace HH\Lib\{C, Dict};

interface HasXHPHelpers
  extends HasXHPBaseHTMLHelpers, XHPHasTransferAttributes {
}
;

/*
 * Use of this trait assumes you have inherited attributes from an HTML element.
 * For the bare minimum, use:
 *
 * attribute :xhp:html_element;
 */
trait XHPHelpers implements HasXHPHelpers {
  require extends :x:composable_element;

  use XHPBaseHTMLHelpers;

  /*
   * Copies all attributes that are set on $this and valid on $target to
   * $target.
   */
  final public function copyAllAttributes(:x:composable_element $target): void {
    $this->transferAttributesImpl($target, keyset[]);
  }

  /*
   * Copies only the non-HTML attributes that are set on $this and valid on
   * $target to $target.
   */
  final public function copyCustomAttributes(
    :x:composable_element $target,
  ): void {
    $this->transferAttributesImpl($target);
  }

  /*
   * Copies all attributes except those specified that are set on $this and
   * valid on $target to $target.
   */
  final public function copyAttributesExcept(
    :x:composable_element $target,
    keyset<string> $ignore,
  ): void {
    $this->transferAttributesImpl($target, $ignore);
  }

  /**
   * Transfers all attributes that are set on $this and valid on $target to
   * $target.
   */
  final public function transferAllAttributes(
    :x:composable_element $target,
  ): void {
    $this->transferAttributesImpl($target, keyset[]);
  }

  /**
   * Transfers only the non-HTML attributes that are set on $this and valid on
   * $target to $target.
   */
  final public function transferCustomAttributes(
    :x:composable_element $target,
  ): void {
    $this->transferAttributesImpl($target, null);
  }

  /**
   * Transfers all attributes except those specified that are set on $this and
   * valid on $target to $target.
   * $this.
   */
  final public function transferAttributesExcept(
    :x:composable_element $target,
    keyset<string> $ignore,
  ): void {
    $this->transferAttributesImpl($target, $ignore);
  }

  /*
   * The grunt work of transfering attributes. Don't call this function
   * directly. Instead, use one of the transfer/copy flavors above.
   */
  final private function transferAttributesImpl(
    :x:composable_element $target,
    ?keyset<string> $ignore = null,
    bool $remove = false,
  ): void {
    $ignore ??= :xhp:html_element::__xhpAttributeDeclaration();

    $compatible = $target::__xhpAttributeDeclaration();
    $transferAttributes = Dict\diff_by_key($this->getAttributes(), $ignore);
    foreach ($transferAttributes as $attribute => $value) {
      if ($target->isAttributeSet($attribute)) {
        continue;
      }
      if (
        C\contains_key($compatible, $attribute) ||
        ReflectionXHPAttribute::IsSpecial($attribute)
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
            :xhp::class2element(static::class).
            ' and '.
            :xhp::class2element($target).
            ' both support the "'.
            $attribute.
            '" '.
            'attribute, but they have different signatures. This is a '.
            'problem because the behavior when transfering or copying '.
            'attributes while validation is on will be different than while '.
            'validation is off. Rename the attribute on at least one of these '.
            'elements to fix this.',
          );
        }
      }
    }
  }

  protected function getAttributeNamesThatAppendValuesOnTransfer(
  ): keyset<string> {
    return keyset['class'];
  }

  final public function transferAttributesToRenderedRoot(
    :x:composable_element $root,
  ): void {
    $attributes = $this->getAttributes();

    // We want to append classes to the root node, instead of replace them,
    // so do this attribute manually and then remove it.
    foreach ($this->getAttributeNamesThatAppendValuesOnTransfer() as $attr) {
      if (
        !(array_key_exists($attr, $attributes) && $root->isAttributeSet($attr))
      ) {
        continue;
      }
      $root_value = $root->getAttribute($attr) as string;
      $this_value = $this->getAttribute($attr) as string;
      if ($root_value === '') {
        $root->setAttribute($attr, $this_value);
      } else if ($this_value !== '') {
        $root->setAttribute($attr, $root_value.' '.$this_value);
      }
    }

    // Transfer all valid attributes to the returned node.
    $this->transferAllAttributes($root);
  }
}
