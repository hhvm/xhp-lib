<?hh // strict

abstract final class XHPAttributeCoercion {
  public static function CoerceToString(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): string {
    if (
      is_array($val)
      || is_object($val)
      /* HH_FIXME[2049] facebook/hhvm#4960 */
      || $val instanceof __PHP_Incomplete_Class
   ) {
     if (!$val instanceof Stringish) {
       throw new XHPInvalidAttributeException(
         $context,
         'string',
         $attr,
         $val,
         );
      }
    }
    return (string)$val;
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
