<?hh
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

xhp class test:attribute_coercion_modes extends :x:element {
  attribute
    int myint,
    float myfloat,
    string mystring,
    bool mybool;

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

class AttributesCoercionModeTest extends Facebook\HackTest\HackTest {
  private ?XHPAttributeCoercionMode $coercionMode;
  private mixed $errorReporting;

  public async function beforeEachTestAsync(): Awaitable<void> {
    $this->coercionMode = XHPAttributeCoercion::GetMode();
    $this->errorReporting = error_reporting();
    /*HH_FIXME[4128] Deprecated, because we are trying to remove this.*/
    :xhp::enableAttributeValidation();
  }

  public async function afterEachTestAsync(): Awaitable<void> {
    $mode = $this->coercionMode;
    invariant($mode !== null, 'did not save coercion mode');
    XHPAttributeCoercion::SetMode($mode);
    error_reporting($this->errorReporting);
    :xhp::disableAttributeValidation();
  }

  public function testNoCoercion(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
    $x =
      <test:attribute_coercion_modes
        myint={3}
        myfloat={1.23}
        mystring="foo"
        mybool={true}
      />;
    expect($x->:myint)->toEqual(3);
    expect($x->:myfloat)->toEqual(1.23);
    expect($x->:mystring)->toEqual('foo');
    expect($x->:mybool)->toEqual(true);
  }

  public function testIntishStringAsInt(): void {
    expect(() ==> {
      XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
      /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
      /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
      $x = <test:attribute_coercion_modes myint="1" />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testFloatAsInt(): void {
    expect(() ==> {
      XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
      /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
      /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
      $x = <test:attribute_coercion_modes myint={1.23} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testIntAsFloat(): void {
    expect(() ==> {
      XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
      /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
      /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
      $x = <test:attribute_coercion_modes myfloat={2} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testIntAsString(): void {
    expect(() ==> {
      XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
      /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
      /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
      $x = <test:attribute_coercion_modes mystring={2} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testIntAsBool(): void {
    expect(() ==> {
      XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
      /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
      /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
      $x = <test:attribute_coercion_modes mybool={1} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testStringAsBool(): void {
    expect(() ==> {
      XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::THROW_EXCEPTION);
      /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
      /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
      $x = <test:attribute_coercion_modes mybool="true" />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testSilentCoercion(): void {
    error_reporting(E_ALL);
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::SILENT);
    /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
    /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
    $x = <test:attribute_coercion_modes mystring={2} />;
    expect($x->:mystring)->toEqual('2');
  }

  public function testLoggingDeprecationCoercion(): void {
    static::markTestSkipped("Needs porting to HackTest (fbexpect#7)");
    error_reporting(E_ALL);
    $exception = null;
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::LOG_DEPRECATION);
    try {
      /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
      /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
      $x = <test:attribute_coercion_modes mystring={2} />;
    } catch (Exception $e) {
      $exception = $e;
    }
    //expect($exception)->toBeInstanceOf('PHPUnit_Framework_Error_Deprecated');

    error_reporting(E_ALL & ~E_USER_DEPRECATED);
    /* HH_IGNORE_ERROR[4110] testing behavior for incorrect types */
    /* HH_IGNORE_ERROR[4343] testing behavior for incorrect types */
    $x = <test:attribute_coercion_modes mystring={2} />;
    expect($x->:mystring)->toEqual('2');
  }
}
