/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace HH\Lib\{C, Str, Vec};

enum XHPAttributeType: int {
  TYPE_STRING = 1;
  TYPE_BOOL = 2;
  TYPE_INTEGER = 3;
  TYPE_ARRAY = 4;
  TYPE_OBJECT = 5;
  TYPE_VAR = 6;
  TYPE_ENUM = 7;
  TYPE_FLOAT = 8;
}

class ReflectionXHPAttribute {
  private XHPAttributeType $type;
  /*
   * OBJECT: string (class name)
   * ENUM: array<string> (enum values)
   * ARRAY: Array decl
   */
  private mixed $extraType;
  private mixed $defaultValue;
  private bool $required;

  private static keyset<string> $specialAttributes = keyset['data', 'aria'];

  public function __construct(private string $name, array<int, mixed> $decl) {
    $this->type = XHPAttributeType::assert($decl[0]);
    $this->extraType = $decl[1];
    $this->defaultValue = $decl[2];
    $this->required = (bool)$decl[3];
  }

  public function getName(): string {
    return $this->name;
  }

  public function getValueType(): XHPAttributeType {
    return $this->type;
  }

  public function isRequired(): bool {
    return $this->required;
  }

  public function hasDefaultValue(): bool {
    return $this->defaultValue !== null;
  }

  public function getDefaultValue(): mixed {
    return $this->defaultValue;
  }

  <<__Memoize>>
  public function getValueClass(): string {
    $t = $this->getValueType();
    invariant(
      $this->getValueType() === XHPAttributeType::TYPE_OBJECT,
      'Tried to get value class for attribute %s of type %s - needed '.'OBJECT',
      $this->getName(),
      XHPAttributeType::getNames()[$this->getValueType()],
    );
    $v = $this->extraType;
    invariant(
      $v is string,
      'Class name for attribute %s is not a string',
      $this->getName(),
    );
    return $v;
  }

  <<__Memoize>>
  public function getEnumValues(): keyset<string> {
    $t = $this->getValueType();
    invariant(
      $this->getValueType() === XHPAttributeType::TYPE_ENUM,
      'Tried to get enum values for attribute %s of type %s - needed '.'ENUM',
      $this->getName(),
      XHPAttributeType::getNames()[$this->getValueType()],
    );
    $v = $this->extraType;
    invariant(
      is_array($v),
      'Class name for attribute %s is not a string',
      $this->getName(),
    );
    return keyset($v);
  }

  /**
   * Returns true if the attribute is a data- or aria- attribute.
   */
  <<__Memoize>>
  public static function IsSpecial(string $attr): bool {
    return strlen($attr) >= 6 &&
      $attr[4] === '-' &&
      C\contains_key(self::$specialAttributes, substr($attr, 0, 4));
  }

  public function __toString(): string {
    switch ($this->getValueType()) {
      case XHPAttributeType::TYPE_STRING:
        $out = 'string';
        break;
      case XHPAttributeType::TYPE_BOOL:
        $out = 'bool';
        break;
      case XHPAttributeType::TYPE_INTEGER:
        $out = 'int';
        break;
      case XHPAttributeType::TYPE_ARRAY:
        $out = 'array';
        break;
      case XHPAttributeType::TYPE_OBJECT:
        $out = $this->getValueClass();
        break;
      case XHPAttributeType::TYPE_VAR:
        $out = 'mixed';
        break;
      case XHPAttributeType::TYPE_ENUM:
        $out = 'enum {';
        $out .= Str\join(
          Vec\map($this->getEnumValues(), $x ==> "'".$x."'"),
          ', ',
        );
        $out .= '}';
        break;
      case XHPAttributeType::TYPE_FLOAT:
        $out = 'float';
        break;
    }
    $out .= ' '.$this->getName();
    if ($this->hasDefaultValue()) {
      $out .= ' = '.var_export($this->getDefaultValue(), true);
    }
    if ($this->isRequired()) {
      $out .= ' @required';
    }
    return $out;
  }
}
