<?hh // decl
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use function Facebook\FBExpect\expect;
// Using decl because this test intentional passes the wrong types for
// attributes

class :test:attribute-coercion-modes extends :x:element {
  attribute
    int myint,
    float myfloat,
    string mystring,
    bool mybool;

  protected function render(): XHPRoot {
    return <div />;
  }
}

class AttributesCoercionModeTest extends PHPUnit_Framework_TestCase {
  private ?XHPAttributeCoercionMode $coercionMode;
  private mixed $errorReporting;

  public function setUp(): void {
    $this->coercionMode = XHPAttributeCoercion::GetMode();
    $this->errorReporting = error_reporting();
    :xhp::enableAttributeValidation();
  }

  public function tearDown(): void {
    $mode = $this->coercionMode;
    invariant($mode !== null, 'did not save coercion mode');
    XHPAttributeCoercion::SetMode($mode);
    error_reporting($this->errorReporting);
    :xhp::disableAttributeValidation();
  }

  public function testNoCoercion(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x =
      <test:attribute-coercion-modes
        myint={3}
        myfloat={1.23}
        mystring="foo"
        mybool={true}
      />;
    expect($x->:myint)->toBeSame(3);
    expect($x->:myfloat)->toBeSame(1.23);
    expect($x->:mystring)->toBeSame('foo');
    expect($x->:mybool)->toBeSame(true);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIntishStringAsInt(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x = <test:attribute-coercion-modes myint="1" />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testFloatAsInt(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x = <test:attribute-coercion-modes myint={1.23} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIntAsFloat(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x = <test:attribute-coercion-modes myfloat={2} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIntAsString(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x = <test:attribute-coercion-modes mystring={2} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIntAsBool(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x = <test:attribute-coercion-modes mybool={1} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testStringAsBool(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x = <test:attribute-coercion-modes mybool="true" />;
  }

  public function testSilentCoercion(): void {
    error_reporting(E_ALL);
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::SILENT);
    $x = <test:attribute-coercion-modes mystring={2} />;
    expect($x->:mystring)->toBeSame('2');
  }

  public function testLoggingDeprecationCoercion(): void {
    error_reporting(E_ALL);
    $exception = null;
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::LOG_DEPRECATION);
    try {
      $x = <test:attribute-coercion-modes mystring={2} />;
    } catch (Exception $e) {
      $exception = $e;
    }
    expect($exception)->toBeInstanceOf('PHPUnit_Framework_Error_Deprecated');

    error_reporting(E_ALL & ~E_USER_DEPRECATED);
    $x = <test:attribute-coercion-modes mystring={2} />;
    expect($x->:mystring)->toBeSame('2');
  }
}
