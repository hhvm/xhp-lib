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

  public static function CoerceToBool(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): bool {
    if (
      $val === 'true'
      || $val === 1
      || $val === '1'
      || $val === $attr
    ) {
      return true;
    }

    if (
      $val === 'false'
      || $val === 0
      || $val === '0'
    ) {
      return false;
    }

    throw new XHPInvalidAttributeException(
      $context,
      'bool',
      $attr,
      $val,
    );
  }

  public static function CoerceToFloat(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): float {
    if (is_numeric($val)) {
      return (float)$val;
    }

    throw new XHPInvalidAttributeException(
      $context,
      'float',
      $attr,
      $val,
    );
  }
}
