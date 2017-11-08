<?hh // strict

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
    $this->assertEquals('<div></div>', $x->toString());
  }

  public function testShapeWithExtraKey(): void {
    $x =
      <test:attribute-types
        /* HH_IGNORE_ERROR[4166] */
        myshape={shape('foo' => 'herp', 'bar' => 'derp', 'baz' => 'extra')}
      />;
    $this->assertEquals('<div></div>', $x->toString());
  }

  public function testShapeWithMissingOptionalKey(): void {
    /* HH_IGNORE_ERROR[4057] */
    $x = <test:attribute-types myshape={shape('foo' => 'herp')} />;
    $this->assertEquals('<div></div>', $x->toString());
  }

  public function testShapeWithMissingRequiredKey(): void {
    $this->expectException(XHPInvalidAttributeException::class);
    /* HH_IGNORE_ERROR[4057] */
    $x = <test:attribute-types myshape={shape()} />;
  }

  public function testValidArrayKeys(): void {
    $x = <test:attribute-types myarraykey="foo" />;
    $this->assertSame('<div></div>', $x->toString());
    $x = <test:attribute-types myarraykey={123} />;
    $this->assertSame('<div></div>', $x->toString());
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
    $this->assertSame('<div></div>', $x->toString());
    $x = <test:attribute-types mynum={1.23} />;
    $this->assertSame('<div></div>', $x->toString());
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
    $this->assertEquals('<div></div>', <test:attribute-types />);
  }

  public function testStringableObjectAsString(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mystring={new StringableTestClass()} />;
    $this->assertSame('StringableTestClass', $x->:mystring);
  }

  public function testIntegerAsString(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mystring={123} />;
    $this->assertSame('123', $x->:mystring);
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
    $this->assertSame(123, $x->:myint);
  }

  public function testFloatAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint={1.23} />;
    $this->assertSame(1, $x->:myint);
  }

  public function testFloatishStringAsInt(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myint="1.23" />;
    $this->assertSame(1, $x->:myint);
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
    $this->assertSame(true, $x->:mybool);
  }

  public function testFalseStringAsBool(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types mybool="false" />;
    $this->assertSame(false, $x->:mybool);
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
    $this->assertSame(true, $x->:mybool);
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
    $this->assertSame(123.0, $x->:myfloat);
  }

  public function testNumericStringsAsFloats(): void {
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myfloat="123" />;
    $this->assertSame(123.0, $x->:myfloat);
    /* HH_IGNORE_ERROR[4110] */
    $x = <test:attribute-types myfloat="1.23" />;
    $this->assertSame(1.23, $x->:myfloat);
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
    $this->assertSame('herp', $x->:mystring);
    $this->assertSame('<div>herp</div>', $x->toString());
  }

  /**
   * @expectedException XHPAttributeRequiredException
   */
  public function testOmittingRequiredAttributes(): void {
    $x = <test:required-attributes />;
    $this->assertNull($x->:mystring);
  }

  public function testProvidingDefaultAttributes(): void {
    $x = <test:default-attributes mystring="herp" />;
    $this->assertSame('herp', $x->:mystring);
    $this->assertSame('<div>herp</div>', $x->toString());
  }

  public function testOmittingDefaultAttributes(): void {
    $x = <test:default-attributes />;
    $this->assertSame('mydefault', $x->:mystring);
    $this->assertSame('<div>mydefault</div>', $x->toString());
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
    $this->assertSame('<div>mydefault</div>', $x->toString());
    $x = <test:default-attributes aria-idonotexist="derp" />;
    $this->assertSame('<div>mydefault</div>', $x->toString());
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
    $this->assertTrue(
      strstr((string)$rattr, "<UNSUPPORTED: legacy callable>") !== false,
      "Incorrect reflection for unsupported `callable` attribute type",
    );
  }
}
