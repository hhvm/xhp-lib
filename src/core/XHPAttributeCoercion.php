<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

enum XHPAttributeCoercionMode: int {
  SILENT = 1; // You're a bad person
  LOG_DEPRECATION = 2; // Default in 2.0
  THROW_EXCEPTION = 3; // Default for 2.1
}

abstract final class XHPAttributeCoercion {
  private static XHPAttributeCoercionMode $mode =
    XHPAttributeCoercionMode::THROW_EXCEPTION;

  public static function GetMode(): XHPAttributeCoercionMode {
    return self::$mode;
  }

  public static function SetMode(XHPAttributeCoercionMode $mode): void {
    self::$mode = $mode;
  }

  private static function LogCoercion(
    :x:composable-element $context,
    string $what,
    string $attr,
    mixed $val,
  ): void {
    switch (self::GetMode()) {
      case XHPAttributeCoercionMode::SILENT:
        // Your forward compatibility is bad, and you should feel bad.
        return;
      case XHPAttributeCoercionMode::LOG_DEPRECATION:
        if (is_object($val)) {
          $val_type = get_class($val);
        } else {
          $val_type = gettype($val);
        }
        trigger_error(
          sprintf(
            'Coercing value of type `%s` to `%s` for attribute `%s` of '.
            'element `%s`',
            $val_type,
            $what,
            $attr,
            :xhp::class2element(get_class($context)),
          ),
          E_USER_DEPRECATED,
        );
        return;
      case XHPAttributeCoercionMode::THROW_EXCEPTION:
        throw new XHPInvalidAttributeException($context, $what, $attr, $val);
    }
  }

  public static function CoerceToString(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): string {
    self::LogCoercion($context, 'string', $attr, $val);
    if ($val is string) {
      return $val;
    }
    if ($val is num) {
      return (string)$val;
    }
    if ($val is Stringish) {
      /* HH_FIXME[4053] */ /* HH_FIXME[4062] */ /* HH_FIXME[4128]
         We know that $val is (not string & Stringish).
         This implies StringishObject, so calling __toString() is safe.
         StringishObject was added in hhvm 4.118 and this branch targets 4.32+. */
      return $val->__toString();
    }

    throw new XHPInvalidAttributeException($context, 'string', $attr, $val);
  }

  public static function CoerceToInt(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): int {
    self::LogCoercion($context, 'int', $attr, $val);
    if (
      (($val is string) && is_numeric($val) && $val !== '') || ($val is float)
    ) {
      return (int)$val;
    }

    throw new XHPInvalidAttributeException($context, 'int', $attr, $val);
  }

  public static function CoerceToBool(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): bool {
    self::LogCoercion($context, 'bool', $attr, $val);
    if ($val === 'true' || $val === 1 || $val === '1' || $val === $attr) {
      return true;
    }

    if ($val === 'false' || $val === 0 || $val === '0') {
      return false;
    }

    throw new XHPInvalidAttributeException($context, 'bool', $attr, $val);
  }

  public static function CoerceToFloat(
    :x:composable-element $context,
    string $attr,
    mixed $val,
  ): float {
    self::LogCoercion($context, 'float', $attr, $val);
    if (is_numeric($val)) {
      return (float)$val;
    }

    throw new XHPInvalidAttributeException($context, 'float', $attr, $val);
  }
}
