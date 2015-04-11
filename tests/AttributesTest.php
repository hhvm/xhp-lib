<?hh // decl
// Using decl because this test intentional passes the wrong types for
// attributes

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
    Map<string, string> mymap;

  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:required-attributes extends :x:element {
  attribute
    string mystring @required;

  protected function render(): XHPRoot {
    return <div>{$this->:mystring}</div>;
  }
}

class :test:default-attributes extends :x:element {
  attribute
    string mystring = 'mydefault';

  protected function render(): XHPRoot {
    return <div>{$this->:mystring}</div>;
  }
}

class EmptyTestClass {}
class StringableTestClass { public function __toString() { return __CLASS__; } }

class AttributesTest extends PHPUnit_Framework_TestCase {
  public function setUp(): void {
    error_reporting(error_reporting() & ~E_USER_DEPRECATED);
  }

  public function testValidTypes(): void {
    $x = <test:attribute-types
      mystring="foo"
      mybool={true}
      myint={123}
      myarray={[1,2,3]}
      myobject={new stdClass()}
      myenum={'foo'}
      myfloat={1.23}
      myvector={Vector { 1, 2, 3 } }
      mymap={Map { 'herp' => 'derp'} }
    />;
    $this->assertEquals('<div></div>', $x->toString());
  }

  public function testNoAttributes(): void {
    $this->assertEquals('<div></div>', <test:attribute-types />);
  }

  public function testStringableObjectAsString(): void {
    $x = <test:attribute-types mystring={new StringableTestClass()} />;
    $this->assertSame('StringableTestClass', $x->:mystring);
  }

  public function testIntegerAsString(): void {
    $x = <test:attribute-types mystring={123} />;
    $this->assertSame('123', $x->:mystring);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testUnstringableObjectAsString(): void {
    $x = <test:attribute-types mystring={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIncompleteObjectAsString(): void {
    $x = <test:attribute-types mystring={new __PHP_Incomplete_Class()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testArrayAsString(): void {
    $x = <test:attribute-types mystring={[]} />;
  }

  public function testIntishStringAsInt(): void {
    $x = <test:attribute-types myint={'123'} />;
    $this->assertSame(123, $x->:myint);
  }

  public function testFloatAsInt(): void {
    $x = <test:attribute-types myint={1.23} />;
    $this->assertSame(1, $x->:myint);
  }

  public function testFloatishStringAsInt(): void {
    $x = <test:attribute-types myint="1.23" />;
    $this->assertSame(1, $x->:myint);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testObjectAsInt(): void {
    $x = <test:attribute-types myint={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIncompleteObjectAsInt(): void {
    $x = <test:attribute-types myint={new __PHP_Incomplete_Class()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testArrayAsInt(): void {
    $x = <test:attribute-types myint={[]} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNumericPrefixStringAsInt(): void {
    $x = <test:attribute-types myint="123derp" />;
  }

  public function testTrueStringAsBool(): void {
    $x = <test:attribute-types mybool="true" />;
    $this->assertSame(true, $x->:mybool);
  }

  public function testFalseStringAsBool(): void {
    $x = <test:attribute-types mybool="false" />;
    $this->assertSame(false, $x->:mybool);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testMixedCaseFalseStringAsBool(): void {
    $x = <test:attribute-types mybool="False" />;
    // 'False' is actually truthy
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNoStringAsBool(): void {
    $x = <test:attribute-types mybool="No" />;
    // 'No' is actually truthy
  }

  public function testAttrNameAsBool(): void {
    // idiomatic - eg checked="checked" 
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
    $x = <test:attribute-types myfloat={123} />;
    $this->assertSame(123.0, $x->:myfloat);
  }

  public function testNumericStringsAsFloats(): void {
    $x = <test:attribute-types myfloat="123" />;
    $this->assertSame(123.0, $x->:myfloat);
    $x = <test:attribute-types myfloat="1.23" />;
    $this->assertSame(1.23, $x->:myfloat);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNonNumericStringAsFloat(): void {
    $x = <test:attribute-types myfloat="herpderp" />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNumericPrefixStringAsFloat(): void {
    $x = <test:attribute-types myfloat="123derp" />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testNotAContainerAsArray(): void {
    $x = <test:attribute-types myarray={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testHackContainerAsArray(): void {
    $x = <test:attribute-types myarray={Vector { 1,2,3 } } />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIncompatibleObjectAsObject(): void {
    $x = <test:attribute-types myobject={new EmptyTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testPassingArrayAsVector(): void {
    $x = <test:attribute-types myvector={[1,2,3]} />;
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
    $x = <test:default-attributes idonotexist="derp" />;
  }

  public function testSpecialAttributes(): void {
    $x = <test:default-attributes data-idonotexist="derp" />;
    $this->assertSame('<div>mydefault</div>', $x->toString());
    $x = <test:default-attributes aria-idonotexist="derp" />;
    $this->assertSame('<div>mydefault</div>', $x->toString());
  }
}
