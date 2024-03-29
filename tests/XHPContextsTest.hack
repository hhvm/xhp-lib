/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\{div, p};
use function Facebook\FBExpect\expect;

final xhp class test:contexts extends x\element {
  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return
      <div>
        <p>{(string)$this->getContext('heading')}</p>
        {$this->getChildren()}
      </div>;
  }
}

final class XHPContextsTest extends Facebook\HackTest\HackTest {
  public async function testContextSimple(): Awaitable<void> {
    $x = <test:contexts />;
    $x->setContext('heading', 'herp');
    expect(await $x->toStringAsync())->toEqual('<div><p>herp</p></div>');
  }

  public async function testContextInsideHTMLElement(): Awaitable<void> {
    $x = <div><test:contexts /></div>;
    $x->setContext('heading', 'herp');
    expect(await $x->toStringAsync())->toEqual(
      '<div><div><p>herp</p></div></div>',
    );
  }

  public async function testNestedContexts(): Awaitable<void> {
    $x = <test:contexts><test:contexts /></test:contexts>;
    $x->setContext('heading', 'herp');
    expect(await $x->toStringAsync())->toEqual(
      '<div><p>herp</p><div><p>herp</p></div></div>',
    );
  }
}
