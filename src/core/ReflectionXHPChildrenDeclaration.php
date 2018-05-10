<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use type Facebook\TypeAssert\IncorrectTypeException;
use namespace Facebook\TypeSpec;

enum XHPChildrenDeclarationType: int {
  NO_CHILDREN = 0;
  ANY_CHILDREN = 1;
  EXPRESSION = ~0;
}

enum XHPChildrenExpressionType: int {
  SINGLE = 0; // :thing
  ANY_NUMBER = 1; // :thing*
  ZERO_OR_ONE = 2; // :thing?
  ONE_OR_MORE = 3; // :thing+
  SUB_EXPR_SEQUENCE = 4; // (expr, expr)
  SUB_EXPR_DISJUNCTION = 5; // (expr | expr)
}

enum XHPChildrenConstraintType: int {
  ANY = 1;
  PCDATA = 2;
  ELEMENT = 3;
  CATEGORY = 4;
  SUB_EXPR = 5;
}

class ReflectionXHPChildrenDeclaration {
  public function __construct(private string $context, private mixed $data) {
  }

  <<__Memoize>>
  public function getType(): XHPChildrenDeclarationType {
    if (is_array($this->data)) {
      return XHPChildrenDeclarationType::EXPRESSION;
    }
    return XHPChildrenDeclarationType::assert($this->data);
  }

  <<__Memoize>>
  public function getExpression(): ReflectionXHPChildrenExpression {
    try {
      $data = TypeSpec\dict_like_array(TypeSpec\int(), TypeSpec\mixed())
        ->assertType($this->data);
      return new ReflectionXHPChildrenExpression($this->context, $data);
    } catch (IncorrectTypeException $_) {
      // handled below
    }

    throw new Exception (
      "Tried to get child expression for XHP class ".
      :xhp::class2element(get_class($this->context)).
      ", but it does not have an expressions."
    );
  }

  public function __toString(): string {
    if ($this->getType() === XHPChildrenDeclarationType::ANY_CHILDREN) {
      return 'any';
    }
    if ($this->getType() === XHPChildrenDeclarationType::NO_CHILDREN) {
      return 'empty';
    }
    return (string)$this->getExpression();
  }
}

class ReflectionXHPChildrenExpression {
  public function __construct(
    private string $context,
    private array<int, mixed> $data,
  ) {
  }

  <<__Memoize>>
  public function getType(): XHPChildrenExpressionType {
    return XHPChildrenExpressionType::assert($this->data[0]);
  }

  <<__Memoize>>
  public function getSubExpressions(
  ): (ReflectionXHPChildrenExpression, ReflectionXHPChildrenExpression) {
    $type = $this->getType();
    invariant(
      $type === XHPChildrenExpressionType::SUB_EXPR_SEQUENCE ||
      $type === XHPChildrenExpressionType::SUB_EXPR_DISJUNCTION,
      'Only disjunctions and sequences have two sub-expressions - in %s',
      :xhp::class2element(get_class($this->context)),
    );
    try {
      $sub_expr_1 = TypeSpec\dict_like_array(TypeSpec\int(), TypeSpec\mixed())
        ->assertType($this->data[1]);
      $sub_expr_2 = TypeSpec\dict_like_array(TypeSpec\int(), TypeSpec\mixed())
        ->assertType($this->data[2]);
      return tuple(
        new ReflectionXHPChildrenExpression($this->context, $sub_expr_1),
        new ReflectionXHPChildrenExpression($this->context, $sub_expr_2),
      );
    } catch (IncorrectTypeException $_) {
      // handled below
    }

    throw new Exception('Data is not subexpressions - in '.$this->context);
  }

  <<__Memoize>>
  public function getConstraintType(): XHPChildrenConstraintType {
    $type = $this->getType();
    invariant(
      $type !== XHPChildrenExpressionType::SUB_EXPR_SEQUENCE &&
      $type !== XHPChildrenExpressionType::SUB_EXPR_DISJUNCTION,
      'Disjunctions and sequences do not have a constraint type - in %s',
      :xhp::class2element(get_class($this->context)),
    );
    return XHPChildrenConstraintType::assert($this->data[1]);
  }

  <<__Memoize>>
  public function getConstraintString(): string {
    $type = $this->getConstraintType();
    invariant(
      $type === XHPChildrenConstraintType::ELEMENT ||
      $type === XHPChildrenConstraintType::CATEGORY,
      'Only element and category constraints have string data - in %s',
      :xhp::class2element(get_class($this->context)),
    );
    $data = $this->data[2];
    invariant(is_string($data), 'Expected string data');
    return $data;
  }

  <<__Memoize>>
  public function getSubExpression(): ReflectionXHPChildrenExpression {
    invariant(
      $this->getConstraintType() === XHPChildrenConstraintType::SUB_EXPR,
      'Only expression constraints have a single sub-expression - in %s',
      $this->context,
    );
    $data = $this->data[2];
    try {
      $data = TypeSpec\dict_like_array(TypeSpec\int(), TypeSpec\mixed())
        ->assertType($this->data[2]);
      return new ReflectionXHPChildrenExpression($this->context, $data);
    } catch (IncorrectTypeException $_) {
      // handled below
    }

    throw new Exception (
      'Expected a sub-expression, got a '.
      is_object($data) ? get_class($data) : gettype($data).
      ' - in '. $this->context
    );
  }

  public function __toString(): string {
    switch ($this->getType()) {
      case XHPChildrenExpressionType::SINGLE:
        return $this->__constraintToString();

      case XHPChildrenExpressionType::ANY_NUMBER:
        return $this->__constraintToString().'*';

      case XHPChildrenExpressionType::ZERO_OR_ONE:
        return $this->__constraintToString().'?';

      case XHPChildrenExpressionType::ONE_OR_MORE:
        return $this->__constraintToString().'+';

      case XHPChildrenExpressionType::SUB_EXPR_SEQUENCE:
        list($e1, $e2) = $this->getSubExpressions();
        return $e1.','.$e2;

      case XHPChildrenExpressionType::SUB_EXPR_DISJUNCTION:
        list($e1, $e2) = $this->getSubExpressions();
        return $e1.'|'.$e2;
    }
  }

  private function __constraintToString(): string {
    switch ($this->getConstraintType()) {
      case XHPChildrenConstraintType::ANY:
        return 'any';

      case XHPChildrenConstraintType::PCDATA:
        return 'pcdata';

      case XHPChildrenConstraintType::ELEMENT:
        return ':'.:xhp::class2element($this->getConstraintString());

      case XHPChildrenConstraintType::CATEGORY:
        return '%'.$this->getConstraintString();

      case XHPChildrenConstraintType::SUB_EXPR:
        return '('.$this->getSubExpression().')';
    }
  }
}
