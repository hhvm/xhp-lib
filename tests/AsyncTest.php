<?hh

class :async:test extends :x:element implements XHPAwaitable {
  use XHPAsync;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <div>{$this->getChildren()}</div>;
  }
}

class AsyncTest extends PHPUnit_Framework_TestCase {
  public function testDiv() {
    $xhp = <async:test>Herp</async:test>;
    $this->assertEquals('<div>Herp</div>', $xhp->toString());
  }

  public function testXFrag() {
    $frag = <x:frag>{1}{2}</x:frag>;
    $xhp = <async:test>{$frag}</async:test>;
    $this->assertEquals('<div>12</div>', $xhp->toString());
  }

  public function testNested() {
    $xhp = <async:test><async:test>herp derp</async:test></async:test>;
    $this->assertEquals('<div><div>herp derp</div></div>', $xhp->toString());
  }

  public function testEmpty() {
    $xhp = <async:test />;
    $this->assertEquals('<div></div>', $xhp->toString());
  }

  public function testNestedEmpty() {
    $xhp = <async:test><async:test /></async:test>;
    $this->assertEquals('<div><div></div></div>', $xhp->toString());
  }

  public function testNestedWithNonAsyncChild() {
    $xhp = <async:test><b>BE BOLD</b></async:test>;
    $this->assertEquals('<div><b>BE BOLD</b></div>', $xhp->toString());
  }
}
