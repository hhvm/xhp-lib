/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\{br, div, head, img, singleton, style};
use function Facebook\FBExpect\expect;
use type Facebook\HackTest\DataProvider;
use namespace HH\Lib\C;

xhp class not_primitive extends x\element {
  <<__Override>>
  public async function renderAsync(): Awaitable<div> {
    return <div><div>I am not a primitive</div></div>;
  }
}

xhp class test:renders_primitive extends x\element {
  <<__Override>>
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

  public async function testCertainActionAreProhibitedAfterRender(
  ): Awaitable<void> {
    $not_primitive = <not_primitive />;
    await $not_primitive->toStringAsync();
    expect(() ==> $not_primitive->setAttribute('class', 'already-rendered'))
      ->toThrow(InvariantException::class, 'after render');

    $div = <div />;
    await $div->toStringAsync();
    expect(() ==> $div->setAttribute('class', 'already-rendered'))->toThrow(
      InvariantException::class,
      'after render',
    );
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
    $x = 'Herp';
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
    $xhp = <div>{'foo<SCRIPT>bar'}</div>;
    expect(await $xhp->toStringAsync())->toEqual(
      '<div>foo&lt;SCRIPT&gt;bar</div>',
    );
  }

  public async function testRendersPrimitive(): Awaitable<void> {
    $xhp = <test:renders_primitive />;
    expect(await $xhp->toStringAsync())->toEqual('<div>123</div>');
  }

  public function provideSingletonElements(): vec<(singleton, string)> {
    return vec[
      // This syntax creates the same object behind the scenes,
      // but I put in an extra test, just in case.
      tuple(<br></br>, '<br>'),
      tuple(<br />, '<br>'),
      tuple(
        <img src="https://example.com/image.jpg" />,
        '<img src="https://example.com/image.jpg">',
      ),
    ];
  }

  <<DataProvider('provideSingletonElements')>>
  public async function testRenderedSingletonsShouldBeVoidElements(
    singleton $void_element,
    string $expect,
  ): Awaitable<void> {
    expect(await $void_element->toStringAsync())->toEqual($expect);
  }

  public async function testUnescapedPCDataElementDoesNotEscapeItsChild(
  ): Awaitable<void> {
    $dangerous_chars = '"\'<>&';
    expect(
      await (<head><style>{$dangerous_chars}</style></head>)->toStringAsync(),
    )->toEqual('<head><style>'.$dangerous_chars.'</style></head>');
  }
}
