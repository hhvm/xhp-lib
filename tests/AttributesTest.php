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
xhp class test:attribute_types extends :x:element {
  attribute
    string mystring,
    bool mybool,
    int myint,
    array<int> myarray,
    stdClass myobject,
    enum {'foo', 'bar'} myenum,
    float myfloat,
    Vector<string> myvector,
    Map<string, string> mymap,
    arraykey myarraykey,
    TMyTestShape myshape,
    num mynum;

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:required_attributes extends :x:element {
  attribute string mystring @required;

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div>{$this->:mystring}</div>;
  }
}

xhp class test:default_attributes extends :x:element {
  attribute string mystring = 'mydefault';

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div>{$this->:mystring}</div>;
  }
}

xhp class test:callable_attribute extends :x:element {
  attribute
    /* HH_FIXME[2049]: callable is an invalid Hack type */
    callable foo; // unsupported in 2.0+
  protected async function renderAsync(): Awaitable<XHPRoot> {
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
    /*HH_FIXME[4128] Deprecated, because we are trying to remove this.*/
    :xhp::enableAttributeValidation();
  }

  public async function afterEachTestAsync(): Awaitable<void> {
    :xhp::disableAttributeValidation();
  }

  public async function testValidTypes(): Awaitable<void> {
    $x =
      <test:attribute_types
        mystring="foo"
        mybool={true}
        myint={123}
        myarray={varray[1, 2, 3]}
        myobject={new stdClass()}
        myenum={'foo'}
        myfloat={1.23}
        myvector={Vector {'1', '2', '3'}}
        mymap={Map {'herp' => 'derp'}}
        myshape={shape('foo' => 'herp', 'bar' => 'derp')}
      />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testShapeWithExtraKey(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(async () ==> {
      $x =
        <test:attribute_types
          /* HH_IGNORE_ERROR[4110] */
          /* HH_IGNORE_ERROR[4343] */
          /* HH_IGNORE_ERROR[4166] */
          myshape={shape('foo' => 'herp', 'bar' => 'derp', 'baz' => 'extra')}
        />;
      expect(await $x->toStringAsync())->toEqual('<div></div>');
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testShapeWithMissingOptionalKey(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(async () ==> {

      /* HH_IGNORE_ERROR[4057] */
      $x = <test:attribute_types myshape={shape('foo' => 'herp')} />;
      expect(await $x->toStringAsync())->toEqual('<div></div>');
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testShapeWithMissingRequiredKey(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(async () ==> {
      /* HH_IGNORE_ERROR[4057] */
      $x = <test:attribute_types myshape={shape()} />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testValidArrayKeys(): Awaitable<void> {
    $x = <test:attribute_types myarraykey="foo" />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:attribute_types myarraykey={123} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testInvalidArrayKeys(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(() ==> {
      $x =
        <test:attribute_types
          myarraykey={/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ 1.23}
        />;
      $x->toString();
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testValidNum(): Awaitable<void> {
    $x = <test:attribute_types mynum={123} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:attribute_types mynum={1.23} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testInvalidNum(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');

    expect(() ==> {
      $x =
        <test:attribute_types
          mynum=/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ "123"
        />;
      $x->toString();
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testNoAttributes(): Awaitable<void> {
    expect(await (<test:attribute_types />)->toStringAsync())->toEqual('<div></div>');
  }

  public async function testStringableObjectAsString(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types mystring={new StringableTestClass()} />;
    expect($x->:mystring)->toEqual('StringableTestClass');
  }

  public async function testIntegerAsString(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types mystring={123} />;
    expect($x->:mystring)->toEqual('123');
  }

  public async function testUnstringableObjectAsString(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          mystring={
            /* HH_FIXME[4110] */ /* HH_FIXME[4343] */ new EmptyTestClass()
          }
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testArrayAsString(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          mystring={/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ varray[]}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testIntishStringAsInt(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types myint={'123'} />;
    expect($x->:myint)->toEqual(123);
  }

  public async function testFloatAsInt(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types myint={1.23} />;
    expect($x->:myint)->toEqual(1);
  }

  public async function testFloatishStringAsInt(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types myint="1.23" />;
    expect($x->:myint)->toEqual(1);
  }

  public async function testObjectAsInt(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          myint={/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ new EmptyTestClass()}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testArrayAsInt(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          myint={/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ varray[]}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testNumericPrefixStringAsInt(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          myint=/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ "123derp"
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testTrueStringAsBool(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types mybool="true" />;
    expect($x->:mybool)->toEqual(true);
  }

  public async function testFalseStringAsBool(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types mybool="false" />;
    expect($x->:mybool)->toEqual(false);
  }

  public async function testMixedCaseFalseStringAsBool(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          mybool=/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ "False"
        />;
    })->toThrow(XHPInvalidAttributeException::class);
    // 'False' is actually truthy
  }

  public async function testNoStringAsBool(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          mybool=/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ "No"
        />;
    })->toThrow(XHPInvalidAttributeException::class);
    // 'No' is actually truthy
  }

  public async function testAttrNameAsBool(): Awaitable<void> {
    // idiomatic - eg checked="checked"
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types mybool="mybool" />;
    expect($x->:mybool)->toEqual(true);
  }

  public async function testInvalidEnumValue(): Awaitable<void> {
    expect(() ==> {
      $x = <test:attribute_types myenum="derp" />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testIntAsFloat(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types myfloat={123} />;
    expect($x->:myfloat)->toEqual(123.0);
  }

  public async function testNumericStringsAsFloats(): Awaitable<void> {
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types myfloat="123" />;
    expect($x->:myfloat)->toEqual(123.0);
    /* HH_IGNORE_ERROR[4110] */
    /* HH_IGNORE_ERROR[4343] */
    $x = <test:attribute_types myfloat="1.23" />;
    expect($x->:myfloat)->toEqual(1.23);
  }

  public async function testNonNumericStringAsFloat(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          myfloat=/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ "herpderp"
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testNumericPrefixStringAsFloat(): Awaitable<void> {
    expect(() ==> {
      $x =
        <test:attribute_types
          myfloat=/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ "123derp"
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testNotAContainerAsArray(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(() ==> {
      $x =
        <test:attribute_types
          myarray={
            /* HH_FIXME[4110] */ /* HH_FIXME[4343] */ new EmptyTestClass()
          }
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testHackContainerAsArray(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(() ==> {
      $x =
        <test:attribute_types
          myarray={/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ Vector {1, 2, 3}}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testIncompatibleObjectAsObject(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(() ==> {
      $x =
        <test:attribute_types
          myobject={
            /* HH_FIXME[4110] */ /* HH_FIXME[4343] */ new EmptyTestClass()
          }
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testPassingArrayAsVector(): Awaitable<void> {
    self::markTestSkipped('Only enums are validated at runtime.');
    expect(() ==> {
      $x =
        <test:attribute_types
          myvector={/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ varray[1, 2, 3]}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }

  public async function testProvidingRequiredAttributes(): Awaitable<void> {
    $x = <test:required_attributes mystring="herp" />;
    expect($x->:mystring)->toEqual('herp');
    expect(await $x->toStringAsync())->toEqual('<div>herp</div>');
  }

  public async function testOmittingRequiredAttributes(): Awaitable<void> {
    expect(() ==> {
      $x = <test:required_attributes />;
      expect($x->:mystring)->toBeNull();
    })->toThrow(XHPAttributeRequiredException::class);
  }

  public async function testProvidingDefaultAttributes(): Awaitable<void> {
    $x = <test:default_attributes mystring="herp" />;
    expect($x->:mystring)->toEqual('herp');
    expect(await $x->toStringAsync())->toEqual('<div>herp</div>');
  }

  public async function testOmittingDefaultAttributes(): Awaitable<void> {
    $x = <test:default_attributes />;
    expect($x->:mystring)->toEqual('mydefault');
    expect(await $x->toStringAsync())->toEqual('<div>mydefault</div>');
  }

  public async function testBogusAttributes(): Awaitable<void> {
    expect(() ==> {
      $x = <test:default_attributes /* HH_FIXME[4053] */ idonotexist="derp" />;
    })->toThrow(XHPAttributeNotSupportedException::class);
  }

  public async function testSpecialAttributes(): Awaitable<void> {
    $x = <test:default_attributes data-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual('<div>mydefault</div>');
    $x = <test:default_attributes aria-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual('<div>mydefault</div>');

    // verify that special attributes actually render
    $x = <div data-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual('<div data-idonotexist="derp"></div>');
    // implicit string cast
    $x = <div data-idonotexist={123} />;
    expect(await $x->toStringAsync())->toEqual('<div data-idonotexist="123"></div>');
    $x = <div aria-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual('<div aria-idonotexist="derp"></div>');

    // special attributes should disappear when null, like all other attributes
    $x = <div data-idonotexist={null} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <div aria-idonotexist={null} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');

    $x = <div data-foo="derp" />;
    $x->setAttribute('data-foo', null);
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testRenderCallableAttribute(): Awaitable<void> {
    self::markTestSkipped('This type has been unsupported since 2.0');
    expect(() ==> {
      $x =
        <test:callable_attribute
          /* HH_IGNORE_ERROR[4110] */
          /* HH_IGNORE_ERROR[4343] */
          foo={function() {
          }}
        />;
    })->toThrow(XHPUnsupportedAttributeTypeException::class);
  }

  public async function testReflectOnCallableAttribute(): Awaitable<void> {
    self::markTestSkipped('This type has been unsupported since 2.0');
    $rxhp = new ReflectionXHPClass(:test:callable_attribute::class);
    $rattr = $rxhp->getAttribute('foo');
    expect(
      strstr($rattr->__toString(), "<UNSUPPORTED: legacy callable>") !== false,
    )
      ->toBeTrue(
        "Incorrect reflection for unsupported `callable` attribute type",
      );
  }

  public async function testAttributeSpread(): Awaitable<void> {
    $x = <test:attribute_types mystring="foo" mybool={true} />;
    $y = <test:attribute_types mystring="bar" {...$x} myint={5} />;
    expect($y->:mystring)->toEqual('foo');
    expect($y->:myint)->toEqual(5);
    expect($y->:mybool)->toEqual(true);

    $attrs = $y->getAttributes()->keys();
    expect($attrs)->toHaveSameContentAs(Vector {'mystring', 'mybool', 'myint'});
  }
}
