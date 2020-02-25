<?hh
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use function Facebook\FBExpect\expect;

xhp class test:no_xhphelpers extends :x:element {
  use XHPBaseHTMLHelpers;
  attribute :xhp:html_element;

  protected function render(): XHPRoot {
    return <div />;
  }
}

xhp class test:xhphelpers extends :x:element {
  use XHPHelpers;
  attribute :xhp:html_element;

  protected function render(): XHPRoot {
    return <div>{$this->getChildren()}</div>;
  }
}

xhp class test:async:no_xhphelpers extends :x:element {
  use XHPAsync;
  use XHPBaseHTMLHelpers;
  attribute :xhp:html_element;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:async:xhphelpers extends :x:element {
  use XHPAsync;
  use XHPHelpers;
  attribute :xhp:html_element;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:with_class_on_root extends :x:element {
  use XHPHelpers;
  attribute :xhp:html_element;

  protected function render(): XHPRoot {
    return <div class="rootClass" />;
  }
}

class XHPHelpersTest extends Facebook\HackTest\HackTest {
  public function testTransferAttributesWithoutHelpers(): void {
    $x = <test:no_xhphelpers data-foo="bar" />;
    expect($x->toString())->toEqual('<div></div>');
    expect($x->getID())->toNotBeEmpty();
    expect($x->toString())->toEqual('<div></div>');
  }

  public function testTransferAttributesAsyncWithoutHelpers(): void {
    $x = <test:async:no_xhphelpers data-foo="bar" />;
    expect($x->toString())->toEqual('<div></div>');
    expect($x->getID())->toNotBeEmpty();
    expect($x->toString())->toEqual('<div></div>');
  }

  public function testTransferAttributesWithHelpers(): void {
    $x = <test:xhphelpers data-foo="bar" />;
    expect($x->toString())->toEqual('<div data-foo="bar"></div>');
    expect($x->getID())->toNotBeEmpty();
    expect('<div id="'.$x->getID().'"></div>')->toEqual($x->toString());
  }

  public function testTransferAttributesAsyncWithHelpers(): void {
    $x = <test:async:xhphelpers data-foo="bar" />;
    expect($x->toString())->toEqual('<div data-foo="bar"></div>');
    expect($x->getID())->toNotBeEmpty();
    expect('<div id="'.$x->getID().'"></div>')->toEqual($x->toString());
  }

  public function testAddClassWithoutHelpers(): void {
    $x = <test:no_xhphelpers class="foo" />;
    $x->addClass("bar");
    $x->conditionClass(true, "herp");
    $x->conditionClass(false, "derp");
    expect($x->:class)->toEqual('foo bar herp');
    expect($x->toString())->toEqual("<div></div>");
  }

  public function testAddClassWithHelpers(): void {
    $x = <test:xhphelpers class="foo" />;
    $x->addClass("bar");
    $x->conditionClass(true, "herp");
    $x->conditionClass(false, "derp");
    expect($x->:class)->toEqual('foo bar herp');
    expect($x->toString())->toEqual('<div class="foo bar herp"></div>');
  }

  public function testRootClassPreserved(): void {
    $x = <test:with_class_on_root />;
    expect($x->toString())->toEqual('<div class="rootClass"></div>');
  }

  public function testTransferedClassesAppended(): void {
    $x = <test:with_class_on_root class="extraClass" />;
    expect($x->toString())->toEqual('<div class="rootClass extraClass"></div>');
  }

  public function testRootClassesNotOverridenByEmptyString(): void {
    $x = <test:with_class_on_root class="" />;
    expect($x->toString())->toEqual('<div class="rootClass"></div>');
  }

  public function testNested(): void {
    $x =
      <test:xhphelpers class="herp">
        <test:xhphelpers class="derp" />
      </test:xhphelpers>;
    expect($x->toString())->toEqual(
      '<div class="herp"><div class="derp"></div></div>',
    );
  }
}
