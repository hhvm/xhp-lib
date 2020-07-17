/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\{br, div, h1, h2, h3, head, img, singleton, style};
use function Facebook\FBExpect\expect;
use type Facebook\HackTest\DataProvider;
use namespace HH\Lib\C;

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

  public function testSelectingChildren(): void {
    $empty = <div></div>;
    $one = <h1 />;
    $two = <h2 />;
    $three = <h3 />;
    $four = <h2 />;
    $five = <h1 />;
    $full = <div>{vec[$one, $two, $three, $four, $five]}</div>;

    expect($empty->getFirstChild())->toBeNull();
    expect($empty->getFirstChild(''))->toBeNull();
    expect($empty->getFirstChild(h2::class))->toBeNull();
    expect($empty->getLastChild())->toBeNull();
    expect($empty->getLastChild(''))->toBeNull();
    expect($empty->getLastChild(h2::class))->toBeNull();

    expect($full->getFirstChild())->toEqual($one);
    // This differs from getChildren(), which treats empty string as wildcards (like null)
    expect($full->getFirstChild(''))->toBeNull();
    expect($full->getFirstChild(h2::class))->toEqual($two);
    // Watch out, this is a painful BC break.
    // The typechecker won't warn you that the class is not named h2.
    // You need to pass Facebook\XHP\HTML\h2 (h2::class)
    expect($full->getFirstChild('h2'))->toBeNull();

    expect($full->getLastChild())->toEqual($five);
    // This uses getChildren() under the hood.
    // So empty string /is/ a wildcard here.
    // Let's make this consistent before v4 is set in stone.
    expect($full->getLastChild(''))->toEqual($five);
    expect($full->getLastChild(h2::class))->toEqual($four);
    expect($full->getFirstChild('h2'))->toBeNull();

    expect($empty->getFirstChildOfType<h2>())->toBeNull();
    expect($empty->getLastChildOfType<h2>())->toBeNull();
    expect($full->getFirstChildOfType<h2>())->toEqual($two);
    expect($full->getLastChildOfType<h2>())->toEqual($four);
    expect($full->getFirstChildOfType<h1>())->toEqual($one);
    expect($full->getLastChildOfType<h1>())->toEqual($five);
    expect($full->getLastChildOfType<br>())->toBeNull();

    expect($empty->getChildrenOfType<h1>())->toBeEmpty();
    expect($full->getChildrenOfType<h1>())->toEqual(vec[$one, $five]);
    expect($full->getChildrenOfType<br>())->toBeEmpty();
  }
}
