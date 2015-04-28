<?hh

class :test:no-xhphelpers extends :x:element {
  use XHPBaseHTMLHelpers;
  attribute :xhp:html-element;

  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:xhphelpers extends :x:element {
  use XHPHelpers;
  attribute :xhp:html-element;

  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:async:no-xhphelpers extends :x:element {
  use XHPAsync;
  use XHPBaseHTMLHelpers;
  attribute :xhp:html-element;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <div />;
  }
}

class :test:async:xhphelpers extends :x:element {
  use XHPAsync;
  use XHPHelpers;
  attribute :xhp:html-element;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <div />;
  }
}

class :test:with-class-on-root extends :x:element {
  use XHPHelpers;
  attribute :xhp:html-element;

  protected function render(): XHPRoot {
    return <div class="rootClass" />;
  }
}

class XHPHelpersTest extends PHPUnit_Framework_TestCase {
  public function testTransferAttributesWithoutHelpers(): void {
    $x = <test:no-xhphelpers data-foo="bar" />;
    $this->assertSame('<div></div>', $x->toString());
    $this->assertNotEmpty($x->getID());
    $this->assertSame('<div></div>', $x->toString());
  }

  public function testTransferAttributesAsyncWithoutHelpers(): void {
    $x = <test:async:no-xhphelpers data-foo="bar" />;
    $this->assertSame('<div></div>', $x->toString());
    $this->assertNotEmpty($x->getID());
    $this->assertSame('<div></div>', $x->toString());
  }

  public function testTransferAttributesWithHelpers(): void {
    $x = <test:xhphelpers data-foo="bar" />;
    $this->assertSame('<div data-foo="bar"></div>', $x->toString());
    $this->assertNotEmpty($x->getID());
    $this->assertSame('<div id="'.$x->getID().'"></div>', $x->toString());
  }

  public function testTransferAttributesAsyncWithHelpers(): void {
    $x = <test:async:xhphelpers data-foo="bar" />;
    $this->assertSame('<div data-foo="bar"></div>', $x->toString());
    $this->assertNotEmpty($x->getID());
    $this->assertSame('<div id="'.$x->getID().'"></div>', $x->toString());
  }

  public function testAddClassWithoutHelpers(): void {
    $x = <test:no-xhphelpers class="foo" />;
    $x->addClass("bar");
    $x->conditionClass(true, "herp");
    $x->conditionClass(false, "derp");
    $this->assertSame('foo bar herp', $x->:class);
    $this->assertSame("<div></div>", $x->toString());
  }

  public function testAddClassWithHelpers(): void {
    $x = <test:xhphelpers class="foo" />;
    $x->addClass("bar");
    $x->conditionClass(true, "herp");
    $x->conditionClass(false, "derp");
    $this->assertSame('foo bar herp', $x->:class);
    $this->assertSame('<div class="foo bar herp"></div>', $x->toString());
  }

  public function testRootClassPreserved(): void {
    $x = <test:with-class-on-root />;
    $this->assertSame('<div class="rootClass"></div>', $x->toString());
  }

  public function testTransferedClassesAppended(): void {
    $x = <test:with-class-on-root class="extraClass" />;
    $this->assertSame(
      '<div class="rootClass extraClass"></div>',
      $x->toString(),
    );
  }

  public function testRootClassesNotOverridenByEmptyString(): void {
    $x = <test:with-class-on-root class="" />;
    $this->assertSame('<div class="rootClass"></div>', $x->toString());
  }
}
