<?hh // strict

abstract final class XHPAttributeCoercion {
  public static function CoerceToString(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): string {
    if (
      is_int($val)
      || is_float($val)
      || $val instanceof Stringish
    ) {
     return (string)$val;
    }

    throw new XHPInvalidAttributeException(
      $context,
      'string',
      $attr,
      $val,
    );
  }

  public static function CoerceToInt(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): int {
    if (
      (is_string($val) && ctype_digit($val) && $val !== '')
      || is_float($val)
    ) {
      return (int) $val;
    }
    throw new XHPInvalidAttributeException(
      $context,
      'int',
      $attr,
      $val,
    );
  }
}
