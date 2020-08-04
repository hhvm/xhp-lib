/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\{
  body,
  br,
  details,
  div,
  h1,
  h2,
  h3,
  head,
  html,
  img,
  p,
  script,
  singleton,
  span,
  style,
};
use namespace Facebook\XHP\HTML\Category;
use function Facebook\FBExpect\expect;
use type Facebook\HackTest\DataProvider;
use namespace HH\Lib\C;

xhp class not_primitive extends x\element {
  <<__Override>>
  public async function renderAsync(): Awaitable<div> {
    return <div><div>I am not a primitive</div></div>;
  }
}

xhp class ui:div extends x\element {
  <<__Override>>
  public async function renderAsync(): Awaitable<div> {
    $div = <div>{$this->getChildren()}</div>;
    $div->requireUniqueID();
    return $div;
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
      ->toThrow(x\UseAfterRenderException::class, 'after render');

    $div = <div />;
    await $div->toStringAsync();
    expect(() ==> $div->setAttribute('class', 'already-rendered'))->toThrow(
      x\UseAfterRenderException::class,
      'after render',
    );
  }

  public async function testRenderingAnElementTwiceThrows(): Awaitable<void> {
    $div = <div />;
    await $div->toStringAsync();
    expect(() ==> $div->toStringAsync())->toThrow(
      x\UseAfterRenderException::class,
      'render XHP element twice',
    );

    $not_primitive = <not_primitive />;
    await $not_primitive->toStringAsync();
    expect(() ==> $not_primitive->toStringAsync())->toThrow(
      x\UseAfterRenderException::class,
      'render XHP element twice',
    );
  }

  public function provideFaultyTrees(): vec<(x\node, string)> {
    $br = <br />;
    $ui_div = <ui:div><div><span /></div></ui:div>;
    /*HHAST_IGNORE_ERROR[DontUseAsioJoin]*/
    \HH\Asio\join($br->toStringAsync());
    /*HHAST_IGNORE_ERROR[DontUseAsioJoin]*/
    \HH\Asio\join($ui_div->toStringAsync());

    return vec[
      tuple(
        <div><span>{$br}</span></div>,
        // Normal path
        'Via XHPPath: HTML\\div -> HTML\\span -> HTML\\br.',
      ),
      tuple(
        <div><ui:div>{$br}</ui:div></div>,
        // Works for custom elements
        'Via XHPPath: HTML\\div -> ui\\div -> HTML\\div -> HTML\\br.',
      ),
      tuple(
        <div><x:frag>{$br}</x:frag></div>,
        // Frags are not included in the XHPPath
        'Via XHPPath: HTML\\div -> HTML\\br.',
      ),
      tuple(
        <div><span>{$ui_div}</span></div>,
        // Custom element at the end of the chain
        'Via XHPPath: HTML\\div -> HTML\\span -> ui\\div.',
      ),
      tuple(
        <div>
          <span />
          <div><span /></div>
          <ui:div><span>{$br}</span></ui:div>
          <ui:div />
        </div>,
        // In a subtree
        'Via XHPPath: HTML\\div -> ui\\div -> HTML\\div -> HTML\span -> HTML\\br.',
      ),
      tuple(
        <div>
          <ui:div><ui:div><span>{$br}</span></ui:div></ui:div>
        </div>,
        // Custom inside of custom
        'Via XHPPath: HTML\\div -> ui\\div -> HTML\\div -> ui\\div -> HTML\\div -> HTML\span -> HTML\\br.',
      ),
    ];
  }

  <<DataProvider('provideFaultyTrees')>>
  public async function testRenderedChildrenOfRenderingTreesThrowExceptionWithPleasantMessages(
    x\node $node,
    string $xhp_path,
  ): Awaitable<void> {
    try {
      await $node->toStringAsync();
      self::fail('Expected an exception, got none');
    } catch (x\UseAfterRenderException $e) {
      $error_message = $e->getMessage();
      expect($error_message)->toContainSubstring('render XHP element twice');
      expect($error_message)->toContainSubstring($xhp_path);
    }
  }

  public async function testNoXHPPathForTheTopLevelNode(): Awaitable<void> {
    $br = <br />;
    $ui_div = <ui:div><div><span /></div></ui:div>;
    concurrent {
      await $br->toStringAsync();
      await $ui_div->toStringAsync();
    }

    try {
      await $br->toStringAsync();
      self::fail('Expected an exception, got none');
    } catch (x\UseAfterRenderException $e) {
      expect($e->getMessage())->toNotContainSubstring('XHPPath');
    }

    try {
      await $ui_div->toStringAsync();
      self::fail('Expected an exception, got none');
    } catch (x\UseAfterRenderException $e) {
      expect($e->getMessage())->toNotContainSubstring('XHPPath');
    }
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
    expect(() ==> $empty->getFirstChildx())->toThrow(\Exception::class);
    expect($empty->getLastChild())->toBeNull();
    expect(() ==> $empty->getLastChildx())->toThrow(\Exception::class);

    expect($full->getFirstChild())->toEqual($one);
    expect($full->getLastChild())->toEqual($five);

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

    $one = <details />;
    $two = <script />;
    $three = <details />;
    $full = <div>{$one}{$two}{$three}</div>;
    expect($full->getFirstChildOfType<Category\Interactive>())->toEqual($one);
    expect($full->getFirstChildOfType<Category\Metadata>())->toEqual($two);
    expect($full->getLastChildOfType<Category\Interactive>())->toEqual($three);
    expect($full->getLastChildOfType<Category\Metadata>())->toEqual($two);

    $body = <body />;
    $html = <html>{$body}</html>;
    // The intent is to make sure that `OfType` still works even if the
    // element does not implement any categories. If body starts
    // implementing categories, pick a different element - don't change
    // this expectation.
    expect($body is \Facebook\XHP\HTML\Category\Category)->toBeFalse();
    expect($html->getFirstChildOfType<body>())->toEqual($body);
  }
}
