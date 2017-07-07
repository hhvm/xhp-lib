<?hh

class :test:for-reflection extends :x:element {
  attribute
    string mystring @required,
    enum {'herp', 'derp'} myenum,
    string mystringwithdefault = 'mydefault';
  children (:div+, (:code, :a)?);
  category %herp, %derp;

  public function render(): XHPRoot {
    return <div />;
  }
}

class ReflectionTest extends PHPUnit_Framework_TestCase {
  private ?ReflectionXHPClass $rxc;

  public function setUp(): void {
    $this->rxc = new ReflectionXHPClass(:test:for-reflection::class);
  }

  public function testClassName(): void {
    $this->assertSame(:test:for-reflection::class, $this->rxc?->getClassName());
  }

  public function testElementName(): void {
    $this->assertSame('test:for-reflection', $this->rxc?->getElementName());
  }

  public function testReflectionClass(): void {
    $rc = $this->rxc?->getReflectionClass();
    $this->assertInstanceOf(ReflectionClass::class, $rc);
    $this->assertSame(:test:for-reflection::class, $rc?->getName());
  }

  public function testGetChildren(): void {
    $children = $this->rxc?->getChildren();
    $this->assertInstanceOf(ReflectionXHPChildrenDeclaration::class, $children);
    $this->assertSame('(:div+,(:code,:a)?)', (string)$children);
  }

  public function testGetAttributes(): void {
    $attrs = $this->rxc?->getAttributes();
    $this->assertNotEmpty($attrs);
    $this->assertEquals(
      Map {
        'mystring' => 'string mystring @required',
        'myenum' => "enum {'herp', 'derp'} myenum",
        'mystringwithdefault' => "string mystringwithdefault = 'mydefault'",
      },
      $attrs?->map($attr ==> (string)$attr),
    );
  }

  public function testGetCategories(): void {
    $categories = $this->rxc?->getCategories();
    $this->assertEquals(Set { 'herp', 'derp' }, $categories);
  }
}
