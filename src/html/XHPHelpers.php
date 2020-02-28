<?hh
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

interface HasXHPHelpers
  extends HasXHPBaseHTMLHelpers, XHPHasTransferAttributes {
}
;

/*
 * Use of this trait assumes you have inherited attributes from an HTML element.
 * For the bare minimum, use:
 *
 * attribute :xhp:html-element;
 */
trait XHPHelpers implements HasXHPHelpers {
  require extends :x:composable_element;

  use XHPBaseHTMLHelpers;

  /*
   * Copies all attributes that are set on $this and valid on $target to
   * $target.
   */
  final public function copyAllAttributes(:x:composable_element $target): void {
    $this->transferAttributesImpl($target, Set {});
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
    Set<string> $ignore,
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
    $this->transferAttributesImpl($target, Set {});
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
    Set<string> $ignore,
  ): void {
    $this->transferAttributesImpl($target, $ignore);
  }

  /*
   * The grunt work of transfering attributes. Don't call this function
   * directly. Instead, use one of the transfer/copy flavors above.
   */
  final private function transferAttributesImpl(
    :x:composable_element $target,
    ?Set<string> $ignore = null,
  ): void {
    if ($ignore === null) {
      $ignore = :xhp:html_element::__xhpAttributeDeclaration();
    } else {
      $ignore = array_fill_keys($ignore->toArray(), true);
    }

    $compatible = new Map($target::__xhpAttributeDeclaration());
    $transferAttributes = array_diff_key($this->getAttributes(), $ignore);
    foreach ($transferAttributes as $attribute => $value) {
      if ($target->isAttributeSet($attribute)) {
        continue;
      }
      if (
        $compatible->containsKey($attribute) ||
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
  ): ImmSet<string> {
    return ImmSet {'class'};
  }

  final public function transferAttributesToRenderedRoot(
    :x:composable_element $root,
  ): void {
    if (:xhp::isAttributeValidationEnabled() && $root is :x:element) {
      if (!($root is HasXHPHelpers)) {
        throw new XHPClassException(
          $this,
          'render() must return an object using the XHPHelpers trait.',
        );
      }

      $rootID = $root->getAttribute('id') ?? null;
      $thisID = $this->getAttribute('id') ?? null;

      if ($rootID !== null && $thisID !== null && $rootID != $thisID) {
        throw new XHPException(
          'ID Collision. '.
          (:xhp::class2element(self::class)).
          ' has an ID '.
          'of "'.
          ($thisID as arraykey).
          '" but it renders into a(n) '.
          (:xhp::class2element(get_class($root))).
          ' which has an ID of "'.
          ($rootID as arraykey).
          '". The latter will get '.
          'overwritten (most often unexpectedly). If you are intending for '.
          'this behavior consider calling $this->removeAttribute(\'id\') '.
          'before returning your node from compose().',
        );
      }
    }

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
