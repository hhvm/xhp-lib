<?hh // decl
// Using decl because this test intentional passes the wrong types for
// attributes

class :test:attribute-coercion-modes extends :x:element {
  attribute int myint, float myfloat, string mystring, bool mybool;

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
  }

  public function tearDown(): void {
    $mode = $this->coercionMode;
    invariant($mode !== null, 'did not save coercion mode');
    XHPAttributeCoercion::SetMode($mode);
    error_reporting($this->errorReporting);
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
    $this->assertSame(3, $x->:myint);
    $this->assertSame(1.23, $x->:myfloat);
    $this->assertSame('foo', $x->:mystring);
    $this->assertSame(true, $x->:mybool);
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
    $this->assertSame('2', $x->:mystring);
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
    $this->assertInstanceOf('PHPUnit_Framework_Error_Deprecated', $exception);

    error_reporting(E_ALL & ~E_USER_DEPRECATED);
    $x = <test:attribute-coercion-modes mystring={2} />;
    $this->assertSame('2', $x->:mystring);
  }
}
