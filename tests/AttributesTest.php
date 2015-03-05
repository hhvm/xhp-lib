<?hh

class :test:attribute-types extends :x:element {
  attribute
    string mystring,
    bool mybool,
    int myint,
    array myarray,
    stdClass myobject,
    enum {'foo', 'bar'} myenum,
    float myfloat;

  protected function render(): XHPRoot {
    return <div />;
  }
}

class EmptyTestClass {}
class StringableTestClass { public function __toString() { return __CLASS__; } }

class AttributesTest extends PHPUnit_Framework_TestCase {
  public function testValidTypes(): void {
    $x = <test:attribute-types
      mystring="foo"
      mybool={true}
      myint={123}
      myarray={[1,2,3]}
      myobject={new stdClass()}
      myenum={'foo'}
      myfloat={1.23}
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
}
