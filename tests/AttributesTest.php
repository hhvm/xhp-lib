<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use function Facebook\FBExpect\expect;

type TMyTestShape = shape('foo' => string, 'bar' => ?string);
class :test:attribute-types extends :x:element {
  attribute
    string mystring,
    bool mybool,
    int myint,
    array myarray,
    stdClass myobject,
    enum {'foo', 'bar'} myenum,
    float myfloat,
    Vector<string> myvector,
    Map<string, string> mymap,
    arraykey myarraykey,
    TMyTestShape myshape,
    num mynum;

  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:required-attributes extends :x:element {
  attribute string mystring @required;

  protected function render(): XHPRoot {
    return <div>{$this->:mystring}</div>;
  }
}

class :test:default-attributes extends :x:element {
  attribute string mystring = 'mydefault';

  protected function render(): XHPRoot {
    return <div>{$this->:mystring}</div>;
  }
}

class :test:callable-attribute extends :x:element {
  attribute
    /* HH_FIXME[2049]: callable is an invalid Hack type */
    callable foo; // unsupported in 2.0+
  protected function render(): XHPRoot {
    $x = $this->getAttribute('foo');
    return <div />;
  }
}

class EmptyTestClass {
}
class StringableTestClass {
  public function __toString(): string {
    return __CLASS__;
  }
}

class AttributesTest extends PHPUnit_Framework_TestCase {
  public function setUp(): void {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::SILENT);
    :xhp::enableAttributeValidation();
  }

  public function tearDown(): void {
    :xhp::disableAttributeValidation();
  }

  public function testValidTypes(): void {
    $x =
      <test:attribute-types
        mystring="foo"
        mybool={true}
        myint={123}
        myarray={[1, 2, 3]}
        myobject={new stdClass()}
        myenum={'foo'}
        myfloat={1.23}
        myvector={Vector { '1', '2', '3' }}
        mymap={Map { 'herp' => 'derp' }}
        myshape={shape('foo' => 'herp', 'bar' => 'derp')}
      />;
    expect($x->toString())->toBePHPEqual('<div></div>');
  }

  public function testShapeWithExtraKey(): void {
    if (HHVM_VERSION_ID >= 32300) {
      $this->expectException(XHPInvalidAttributeException::class);
    }

    $x =
      <test:attribute-types
        /* HH_IGNORE_ERROR[4166] */
        myshape={shape('foo' => 'herp', 'bar' => 'derp', 'baz' => 'extra')}
      />;
    expect($x->toString())->toBePHPEqual('<div></div>');
  }

  public function testShapeWithMissingOptionalKey(): void {
    if (HHVM_VERSION_ID >= 32300) {
      $this->expectException(XHPInvalidAttributeException::class);
    }

    /* HH_IGNORE_ERROR[4057] */
    $x = <test:attribute-types myshape={shape('foo' => 'herp')} />;
    expect($x->toString())->toBePHPEqual('<div></div>');
  }

  public function testShapeWithMissingRequiredKey(): void {
    $this->expectException(XHPInvalidAttributeException::class);
    /* HH_IGNORE_ERROR[4057] */
    $x = <test:attribute-types myshape={shape()} />;
  }

  public function testValidArrayKeys(): void {
    $x = <test:attribute-types myarraykey="foo" />;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <test:attribute-types myarraykey={123} />;
    expect($x->toString())->toBeSame('<div></div>');
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testInvalidArrayKeys(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myarraykey={1.23} />;
    $x->toString();
  }

  public function testValidNum(): void {
    $x = <test:attribute-types mynum={123} />;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <test:attribute-types mynum={1.23} />;
    expect($x->toString())->toBeSame('<div></div>');
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testInvalidNum(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mynum="123" />;
    $x->toString();
  }

  public function testNoAttributes(): void {
    expect(<test:attribute-types />)->toBePHPEqual('<div></div>');
  }

  public function testStringableObjectAsString(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mystring={new StringableTestClass()} />;
    expect($x->:mystring)->toBeSame('StringableTestClass');
  }

  public function testIntegerAsString(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mystring={123} />;
    expect($x->:mystring)->toBeSame('123');
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testUnstringableObjectAsString(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mystring={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIncompleteObjectAsString(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mystring={new __PHP_Incomplete_Class()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testArrayAsString(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mystring={[]} />;
  }

  public function testIntishStringAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint={'123'} />;
    expect($x->:myint)->toBeSame(123);
  }

  public function testFloatAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint={1.23} />;
    expect($x->:myint)->toBeSame(1);
  }

  public function testFloatishStringAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint="1.23" />;
    expect($x->:myint)->toBeSame(1);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testObjectAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIncompleteObjectAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint={new __PHP_Incomplete_Class()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testArrayAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint={[]} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNumericPrefixStringAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint="123derp" />;
  }

  public function testTrueStringAsBool(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mybool="true" />;
    expect($x->:mybool)->toBeSame(true);
  }

  public function testFalseStringAsBool(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mybool="false" />;
    expect($x->:mybool)->toBeSame(false);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testMixedCaseFalseStringAsBool(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mybool="False" />;
    // 'False' is actually truthy
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNoStringAsBool(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mybool="No" />;
    // 'No' is actually truthy
  }

  public function testAttrNameAsBool(): void {
    // idiomatic - eg checked="checked"
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mybool="mybool" />;
    expect($x->:mybool)->toBeSame(true);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testInvalidEnumValue(): void {
    $x = <test:attribute-types myenum="derp" />;
  }

  public function testIntAsFloat(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myfloat={123} />;
    expect($x->:myfloat)->toBeSame(123.0);
  }

  public function testNumericStringsAsFloats(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myfloat="123" />;
    expect($x->:myfloat)->toBeSame(123.0);
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myfloat="1.23" />;
    expect($x->:myfloat)->toBeSame(1.23);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNonNumericStringAsFloat(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myfloat="herpderp" />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNumericPrefixStringAsFloat(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myfloat="123derp" />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNotAContainerAsArray(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myarray={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testHackContainerAsArray(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myarray={Vector { 1, 2, 3 }} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIncompatibleObjectAsObject(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myobject={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testPassingArrayAsVector(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myvector={[1, 2, 3]} />;
  }

  public function testProvidingRequiredAttributes(): void {
    $x = <test:required-attributes mystring="herp" />;
    expect($x->:mystring)->toBeSame('herp');
    expect($x->toString())->toBeSame('<div>herp</div>');
  }

  /**
   * @expectedException XHPAttributeRequiredException
   */
  public function testOmittingRequiredAttributes(): void {
    $x = <test:required-attributes />;
    expect($x->:mystring)->toBeNull();
  }

  public function testProvidingDefaultAttributes(): void {
    $x = <test:default-attributes mystring="herp" />;
    expect($x->:mystring)->toBeSame('herp');
    expect($x->toString())->toBeSame('<div>herp</div>');
  }

  public function testOmittingDefaultAttributes(): void {
    $x = <test:default-attributes />;
    expect($x->:mystring)->toBeSame('mydefault');
    expect($x->toString())->toBeSame('<div>mydefault</div>');
  }

  /**
   * @expectedException XHPAttributeNotSupportedException
   */
  public function testBogusAttributes(): void {
    /* HH_IGNORE_ERROR[4053] */
    $x = <test:default-attributes idonotexist="derp" />;
  }

  public function testSpecialAttributes(): void {
    $x = <test:default-attributes data-idonotexist="derp" />;
    expect($x->toString())->toBeSame('<div>mydefault</div>');
    $x = <test:default-attributes aria-idonotexist="derp" />;
    expect($x->toString())->toBeSame('<div>mydefault</div>');
  }

  /**
   * @expectedException XHPUnsupportedAttributeTypeException
   */
  public function testRenderCallableAttribute(): void {
    $x =
      <test:callable-attribute
        /* HH_IGNORE_ERROR[4110] */
        foo={function() {
        }}
      />;
  }

  public function testReflectOnCallableAttribute(): void {
    $rxhp = new ReflectionXHPClass(:test:callable-attribute::class);
    $rattr = $rxhp->getAttribute('foo');
    expect(strstr((string)$rattr, "<UNSUPPORTED: legacy callable>") !== false)
      ->toBeTrue(
        "Incorrect reflection for unsupported `callable` attribute type",
      );
  }

  public function testAttributeSpread(): void {
    $x = <test:attribute-types mystring="foo" mybool={true} />;
    $y = <test:attribute-types mystring="bar" {...$x} myint={5} />;
    expect($y->:mystring)->toBeSame('foo');
    expect($y->:myint)->toBeSame(5);
    expect($y->:mybool)->toBeSame(true);

    $attrs = $y->getAttributes()->keys();
    expect($attrs)->toBePHPEqual(Vector { 'mystring', 'mybool', 'myint' });
  }
}
