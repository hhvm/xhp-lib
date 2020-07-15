/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\{XHPAttributeClobbering_DEPRECATED, XHPHTMLHelpers, div};
use function Facebook\FBExpect\expect;

xhp class test:no_xhphelpers extends x\element {
  use XHPHTMLHelpers;
  attribute :Facebook:XHP:HTML:element;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div />;
  }
}

xhp class test:xhphelpers extends x\element {
  use XHPAttributeClobbering_DEPRECATED;
  attribute :Facebook:XHP:HTML:element;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div>{$this->getChildren()}</div>;
  }
}

xhp class test:async:no_xhphelpers extends x\element {
  use XHPHTMLHelpers;
  attribute :Facebook:XHP:HTML:element;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div />;
  }
}

xhp class test:async:xhphelpers extends x\element {
  use XHPAttributeClobbering_DEPRECATED;
  attribute :Facebook:XHP:HTML:element;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div />;
  }
}

xhp class test:with_class_on_root extends x\element {
  use XHPAttributeClobbering_DEPRECATED;
  attribute :Facebook:XHP:HTML:element;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div class="rootClass" />;
  }
}

class XHPAttributeClobbering_DEPRECATEDTest extends Facebook\HackTest\HackTest {
  public async function testTransferAttributesWithoutHelpers(
  ): Awaitable<void> {
    $x = <test:no_xhphelpers data-foo="bar" />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:no_xhphelpers data-foo="bar" />;
    expect($x->getID())->toNotBeEmpty();
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testTransferAttributesAsyncWithoutHelpers(
  ): Awaitable<void> {
    $x = <test:async:no_xhphelpers data-foo="bar" />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:async:no_xhphelpers data-foo="bar" />;
    expect($x->getID())->toNotBeEmpty();
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testTransferAttributesWithHelpers(): Awaitable<void> {
    $x = <test:xhphelpers data-foo="bar" />;
    expect(await $x->toStringAsync())->toEqual('<div data-foo="bar"></div>');
    $x = <test:xhphelpers data-foo="bar" />;
    expect($x->getID())->toNotBeEmpty();
    expect(await $x->toStringAsync())->toEqual(
      '<div data-foo="bar" id="'.$x->getID().'"></div>',
    );
  }

  public async function testTransferAttributesAsyncWithHelpers(
  ): Awaitable<void> {
    $x = <test:async:xhphelpers data-foo="bar" />;
    expect(await $x->toStringAsync())->toEqual('<div data-foo="bar"></div>');
    $x = <test:async:xhphelpers data-foo="bar" />;
    expect($x->getID())->toNotBeEmpty();
    expect(await $x->toStringAsync())->toEqual(
      '<div data-foo="bar" id="'.$x->getID().'"></div>',
    );
  }

  public async function testAddClassWithoutHelpers(): Awaitable<void> {
    $x = <test:no_xhphelpers class="foo" />;
    $x->addClass('bar');
    $x->conditionClass(true, 'herp');
    $x->conditionClass(false, 'derp');
    expect($x->:class)->toEqual('foo bar herp');
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testAddClassWithHelpers(): Awaitable<void> {
    $x = <test:xhphelpers class="foo" />;
    $x->addClass('bar');
    $x->conditionClass(true, 'herp');
    $x->conditionClass(false, 'derp');
    expect($x->:class)->toEqual('foo bar herp');
    expect(await $x->toStringAsync())->toEqual(
      '<div class="foo bar herp"></div>',
    );
  }

  public async function testRootClassPreserved(): Awaitable<void> {
    $x = <test:with_class_on_root />;
    expect(await $x->toStringAsync())->toEqual('<div class="rootClass"></div>');
  }

  public async function testTransferedClassesAppended(): Awaitable<void> {
    $x = <test:with_class_on_root class="extraClass" />;
    expect(await $x->toStringAsync())->toEqual(
      '<div class="rootClass extraClass"></div>',
    );
  }

  public async function testRootClassesNotOverridenByEmptyString(
  ): Awaitable<void> {
    $x = <test:with_class_on_root class="" />;
    expect(await $x->toStringAsync())->toEqual('<div class="rootClass"></div>');
  }

  public async function testNested(): Awaitable<void> {
    $x =
      <test:xhphelpers class="herp">
        <test:xhphelpers class="derp" />
      </test:xhphelpers>;
    expect(await $x->toStringAsync())->toEqual(
      '<div class="herp"><div class="derp"></div></div>',
    );
  }
}
