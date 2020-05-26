/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use function Facebook\FBExpect\expect;
use namespace HH\Lib\C;

xhp class test:renders_primitive extends x\element {
  protected async function renderAsync(): Awaitable<x\node> {
    return <x:frag><div>123</div></x:frag>;
  }
}

class BasicsTest extends Facebook\HackTest\HackTest {
  public async function testDivWithString(): Awaitable<void> {
    $xhp =
      <div>
        Hello, world.
      </div>;
    expect(await $xhp->toStringAsync())->toEqual('<div> Hello, world. </div>');
  }

  public async function testFragWithString(): Awaitable<void> {
    $xhp = <x:frag>Derp</x:frag>;
    expect(await $xhp->toStringAsync())->toEqual('Derp');
  }

  public async function testDivWithChild(): Awaitable<void> {
    $xhp = <div><div>Herp</div></div>;
    expect(await $xhp->toStringAsync())->toEqual('<div><div>Herp</div></div>');
  }

  public async function testInterpolation(): Awaitable<void> {
    $x = "Herp";
    $xhp = <div>{$x}</div>;
    expect(await $xhp->toStringAsync())->toEqual('<div>Herp</div>');
  }

  public async function testXFrag(): Awaitable<void> {
    $x = 'herp';
    $y = 'derp';
    $frag = <x:frag>{$x}{$y}</x:frag>;
    expect(C\count($frag->getChildren()))->toEqual(2);
    $xhp = <div>{$frag}</div>;
    expect(await $xhp->toStringAsync())->toEqual('<div>herpderp</div>');
  }

  public async function testEscaping(): Awaitable<void> {
    $xhp = <div>{"foo<SCRIPT>bar"}</div>;
    expect(await $xhp->toStringAsync())->toEqual(
      '<div>foo&lt;SCRIPT&gt;bar</div>',
    );
  }

  public async function testElement2Class(): Awaitable<void> {
    expect(\Facebook\XHP\element2class('div'))->toEqual(:div::class);
  }

  public async function testClass2Element(): Awaitable<void> {
    expect(\Facebook\XHP\class2element(:div::class))->toEqual('div');
  }

  public async function testRendersPrimitive(): Awaitable<void> {
    $xhp = <test:renders_primitive />;
    expect(await $xhp->toStringAsync())->toEqual('<div>123</div>');
  }
}
