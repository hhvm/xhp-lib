<?hh

class :test:contexts extends :x:element {
  protected function render(): XHPRoot {
    return
      <div>
        <p>{(string) $this->getContext('heading')}</p>
        {$this->getChildren()}
      </div>;
  }
}

class XHPContextsTest extends PHPUnit_Framework_TestCase {
  public function testContextSimple(): void {
    $x = <test:contexts />;
    $x->setContext('heading', 'herp');
    $this->assertSame('<div><p>herp</p></div>', $x->toString());
  }

  public function testContextInsideHTMLElement(): void {
    $x = <div><test:contexts /></div>;
    $x->setContext('heading', 'herp');
    $this->assertSame('<div><div><p>herp</p></div></div>', $x->toString());
  }

  public function testNestedContexts(): void {
    $x = <test:contexts><test:contexts /></test:contexts>;
    $x->setContext('heading', 'herp');
    $this->assertSame(
      '<div><p>herp</p><div><p>herp</p></div></div>',
      $x->toString(),
    );
  }
}
