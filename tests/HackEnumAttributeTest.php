<?hh

enum TestEnum: int {
  HERP = 1;
  DERP = 2;
}

class :test:hack-enum-attribute extends :x:element {
  attribute
    TestEnum foo @required;
  protected function render(): XHPRoot {
    $foo = TestEnum::getNames()[$this->:foo];
    return <div>{$foo}</div>;
  }
}

class HackEnumAttributesTest extends PHPUnit_Framework_TestCase {
  public function testValidValues(): void {
    $x = <test:hack-enum-attribute foo={TestEnum::HERP} />;
    $this->assertSame('<div>HERP</div>', $x->toString());
    $x = <test:hack-enum-attribute foo={TestEnum::DERP} />;
    $this->assertSame('<div>DERP</div>', $x->toString());
  }

  public function testValidRawValues(): void {
    // UNSAFE
    $x = <test:hack-enum-attribute foo={1} />;
    $this->assertSame('<div>HERP</div>', $x->toString());
    $x = <test:hack-enum-attribute foo={2} />;
    $this->assertSame('<div>DERP</div>', $x->toString());
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testInvalidValue(): void {
    // UNSAFE
    $x = <test:hack-enum-attribute foo={0} />;
  }
}
