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

class AttributesTest extends Facebook\HackTest\HackTest {
  public async function beforeEachTestAsync(): Awaitable<void> {
    XHPAttributeCoercion::SetMode(XHPAttributeCoercionMode::SILENT);
    :xhp::enableAttributeValidation();
  }

  public async function afterEachTestAsync(): Awaitable<void> {
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
        myvector={Vector {'1', '2', '3'}}
        mymap={Map {'herp' => 'derp'}}
        myshape={shape('foo' => 'herp', 'bar' => 'derp')}
      />;
    expect($x->toString())->toBePHPEqual('<div></div>');
  }

  public function testShapeWithExtraKey(): void {
    expect(() ==> {

      $x =
        <test:attribute-types
          /* HH_IGNORE_ERROR[4110] */
          /* HH_IGNORE_ERROR[4166] 
          Older HHVM versions may not handle this expression well
          HHVM 4.14 is fine with it.*/
          myshape={shape('foo' => 'herp', 'bar' => 'derp', 'baz' => 'extra')}
        />;
      expect($x->toString())->toBePHPEqual('<div></div>');
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testShapeWithMissingOptionalKey(): void {
    expect(() ==> {

      /* HH_IGNORE_ERROR[4057] */
      $x = <test:attribute-types myshape={shape('foo' => 'herp')} />;
      expect($x->toString())->toBePHPEqual('<div></div>');
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testShapeWithMissingRequiredKey(): void {
    expect(() ==> {
      /* HH_IGNORE_ERROR[4057] */
      $x = <test:attribute-types myshape={shape()} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testValidArrayKeys(): void {
    $x = <test:attribute-types myarraykey="foo" />;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <test:attribute-types myarraykey={123} />;
    expect($x->toString())->toBeSame('<div></div>');
  }

  public function testInvalidArrayKeys(): void {
    expect(() ==> {
      $x = <test:attribute-types myarraykey={/* HH_FIXME[4110] */ 1.23} />;
      $x->toString();
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testValidNum(): void {
    $x = <test:attribute-types mynum={123} />;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <test:attribute-types mynum={1.23} />;
    expect($x->toString())->toBeSame('<div></div>');
  }

  public function testInvalidNum(): void {
    expect(() ==> {
      $x = <test:attribute-types mynum=/* HH_FIXME[4110] */ "123" />;
      $x->toString();
    })->toThrow(XHPInvalidAttributeException::class);
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

  public function testUnstringableObjectAsString(): void {
    expect(() ==> {
      $x =
        <test:attribute-types
          mystring={/* HH_FIXME[4110] */ new EmptyTestClass()}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testArrayAsString(): void {
    expect(() ==> {
      $x = <test:attribute-types mystring={/* HH_FIXME[4110] */ []} />;
    })->toThrow(XHPInvalidAttributeException::class);
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

  public function testObjectAsInt(): void {
    expect(() ==> {
      $x =
        <test:attribute-types
          myint={/* HH_FIXME[4110] */ new EmptyTestClass()}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testArrayAsInt(): void {
    expect(() ==> {
      $x = <test:attribute-types myint={/* HH_FIXME[4110] */ []} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testNumericPrefixStringAsInt(): void {
    expect(() ==> {
      $x = <test:attribute-types myint=/* HH_FIXME[4110] */ "123derp" />;
    })->toThrow(XHPInvalidAttributeException::class);
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

  public function testMixedCaseFalseStringAsBool(): void {
    expect(() ==> {
      $x = <test:attribute-types mybool=/* HH_FIXME[4110] */ "False" />;
    })->toThrow(XHPInvalidAttributeException::class);
    // 'False' is actually truthy
  }

  public function testNoStringAsBool(): void {
    expect(() ==> {
      $x = <test:attribute-types mybool=/* HH_FIXME[4110] */ "No" />;
    })->toThrow(XHPInvalidAttributeException::class);
    // 'No' is actually truthy
  }

  public function testAttrNameAsBool(): void {
    // idiomatic - eg checked="checked"
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mybool="mybool" />;
    expect($x->:mybool)->toBeSame(true);
  }

  public function testInvalidEnumValue(): void {
    expect(() ==> {
      $x = <test:attribute-types myenum="derp" />;
    })->toThrow(XHPInvalidAttributeException::class);
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

  public function testNonNumericStringAsFloat(): void {
    expect(() ==> {
      $x = <test:attribute-types myfloat=/* HH_FIXME[4110] */ "herpderp" />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testNumericPrefixStringAsFloat(): void {
    expect(() ==> {
      $x = <test:attribute-types myfloat=/* HH_FIXME[4110] */ "123derp" />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testNotAContainerAsArray(): void {
    expect(() ==> {
      $x =
        <test:attribute-types
          myarray={/* HH_FIXME[4110] */ new EmptyTestClass()}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testHackContainerAsArray(): void {
    expect(() ==> {
      $x =
        <test:attribute-types
          myarray={/* HH_FIXME[4110] */ Vector {1, 2, 3}}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testIncompatibleObjectAsObject(): void {
    expect(() ==> {
      $x =
        <test:attribute-types
          myobject={/* HH_FIXME[4110] */ new EmptyTestClass()}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testPassingArrayAsVector(): void {
    expect(() ==> {
      $x = <test:attribute-types myvector={/* HH_FIXME[4110] */ [1, 2, 3]} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public function testProvidingRequiredAttributes(): void {
    $x = <test:required-attributes mystring="herp" />;
    expect($x->:mystring)->toBeSame('herp');
    expect($x->toString())->toBeSame('<div>herp</div>');
  }

  public function testOmittingRequiredAttributes(): void {
    expect(() ==> {
      $x = <test:required-attributes />;
      expect($x->:mystring)->toBeNull();
    })->toThrow(XHPAttributeRequiredException::class);
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

  public function testBogusAttributes(): void {
    expect(() ==> {
      $x = <test:default-attributes /* HH_FIXME[4053] */ idonotexist="derp" />;
    })->toThrow(XHPAttributeNotSupportedException::class);
  }

  public function testSpecialAttributes(): void {
    $x = <test:default-attributes data-idonotexist="derp" />;
    expect($x->toString())->toBeSame('<div>mydefault</div>');
    $x = <test:default-attributes aria-idonotexist="derp" />;
    expect($x->toString())->toBeSame('<div>mydefault</div>');

    // verify that special attributes actually render
    $x = <div data-idonotexist="derp" />;
    expect($x->toString())->toBeSame('<div data-idonotexist="derp"></div>');
    // implicit string cast
    $x = <div data-idonotexist={123} />;
    expect($x->toString())->toBeSame('<div data-idonotexist="123"></div>');
    $x = <div aria-idonotexist="derp" />;
    expect($x->toString())->toBeSame('<div aria-idonotexist="derp"></div>');

    // special attributes should disappear when null, like all other attributes
    $x = <div data-idonotexist={null} />;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <div aria-idonotexist={null} />;
    expect($x->toString())->toBeSame('<div></div>');

    $x = <div data-foo="derp" />;
    $x->setAttribute('data-foo', null);
    expect($x->toString())->toBeSame('<div></div>');
  }

  public function testRenderCallableAttribute(): void {
    expect(() ==> {
      $x =
        <test:callable-attribute
          /* HH_IGNORE_ERROR[4110] */
          foo={function() {
          }}
        />;
    })->toThrow(XHPUnsupportedAttributeTypeException::class);
  }

  public function testReflectOnCallableAttribute(): void {
    $rxhp = new ReflectionXHPClass(:test:callable-attribute::class);
    $rattr = $rxhp->getAttribute('foo');
    expect(
      strstr($rattr->__toString(), "<UNSUPPORTED: legacy callable>") !== false,
    )
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
    expect($attrs)->toBePHPEqual(Vector {'mystring', 'mybool', 'myint'});
  }
}
