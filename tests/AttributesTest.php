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

class NotAStringableTestClass {}
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
    $this->assertEquals('<div></div>', $x->toString());
    $this->assertSame('StringableTestClass', $x->:mystring);
  }

  public function testIntegerAsString(): void {
    $x = <test:attribute-types mystring={123} />;
    $this->assertEquals('<div></div>', $x->toString());
    $this->assertSame('123', $x->:mystring);
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testUnstringableObjectAsString(): void {
    $x = <test:attribute-types mystring={new NotAStringableTestClass()} />;
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testIncompleteObjectAsString(): void {
    $x = <test:attribute-types mystring={new __PHP_Incomplete_Class()} />;
  }
}
