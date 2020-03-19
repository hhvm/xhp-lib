/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Elements\Core as x;
use function Facebook\FBExpect\expect;

use type Facebook\HackTest\DataProvider;

xhp class test:verbatim_root extends x\element {
  attribute x\node root @required;

  protected async function renderAsync(): Awaitable<x\node> {
    return $this->:root;
  }
}

xhp class test:verbatim_root:async extends x\element {

  attribute x\node root @required;

  protected async function renderAsync(): Awaitable<x\node> {
    return $this->:root;
  }
}

class XHPChildFlushTest extends Facebook\HackTest\HackTest {
  public function xhpRootProvider(): vec<(x\xhp, string)> {
    return vec[
      tuple(<div />, '<div></div>'),
      tuple(<div><div /><div /></div>, '<div><div></div><div></div></div>'),
      tuple(<test:verbatim_root root={<div />} />, '<div></div>'),
      tuple(<x:frag><div /></x:frag>, '<div></div>'),
      tuple(<x:frag><div /><div /></x:frag>, '<div></div><div></div>'),
      tuple(
        <test:verbatim_root root={<x:frag><div /><div /></x:frag>} />,
        '<div></div><div></div>',
      ),
      tuple(
        <test:verbatim_root root={<test:verbatim_root root={<div />} />} />,
        '<div></div>',
      ),
      tuple(<test:verbatim_root:async root={<div />} />, '<div></div>'),
    ];
  }

  <<DataProvider('xhpRootProvider')>>
  public async function testSynchronous(
    x\node $root,
    string $expected,
  ): Awaitable<void> {
    $elem = <test:verbatim_root />;
    $elem->setContext('root', $root);
    expect(await $elem->toStringAsync())->toEqual($expected);
  }

  <<DataProvider('xhpRootProvider')>>
  public async function testAsynchronous(
    x\node $root,
    string $expected,
  ): Awaitable<void> {
    $elem = <test:verbatim_root:async />;
    $elem->setContext('root', $root);
    expect(await $elem->toStringAsync())->toEqual($expected);
  }
}
