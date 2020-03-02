<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace HH\Lib\Math;
use function Facebook\FBExpect\expect;
use type Facebook\HackTest\DataProvider;

xhp class async:test extends :x:element {

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div>{$this->getChildren()}</div>;
  }
}

xhp class test:xfrag_wrap extends :x:element {

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <x:frag>{$this->getChildren()}</x:frag>;
  }
}

xhp class test:async_xfrag_wrap extends :x:element {

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <x:frag>{$this->getChildren()}</x:frag>;
  }
}

xhp class async:par_test extends :x:element {

  attribute string label @required;

  public static vec<(string, string)> $log = vec[];

  protected async function renderAsync(): Awaitable<XHPRoot> {
    $label = $this->:label;
    self::$log[] = tuple($label, 'start');
    await RescheduleWaitHandle::create(RescheduleWaitHandle::QUEUE_DEFAULT, 0);
    self::$log[] = tuple($label, 'mid');
    await RescheduleWaitHandle::create(RescheduleWaitHandle::QUEUE_DEFAULT, 0);
    self::$log[] = tuple($label, 'finish');
    return <div>{$label}</div>;
  }
}

class AsyncTest extends Facebook\HackTest\HackTest {
  public async function testDiv(): Awaitable<void> {
    $xhp = <async:test>Herp</async:test>;
    expect(await $xhp->toStringAsync())->toEqual('<div>Herp</div>');
  }

  public async function testXFrag(): Awaitable<void> {
    $frag = <x:frag>{1}{2}</x:frag>;
    $xhp = <async:test>{$frag}</async:test>;
    expect(await $xhp->toStringAsync())->toEqual('<div>12</div>');
  }

  public async function testNested(): Awaitable<void> {
    $xhp = <async:test><async:test>herp derp</async:test></async:test>;
    expect(await $xhp->toStringAsync())->toEqual('<div><div>herp derp</div></div>');
  }

  public async function testEmpty(): Awaitable<void> {
    $xhp = <async:test />;
    expect(await $xhp->toStringAsync())->toEqual('<div></div>');
  }

  public async function testNestedEmpty(): Awaitable<void> {
    $xhp = <async:test><async:test /></async:test>;
    expect(await $xhp->toStringAsync())->toEqual('<div><div></div></div>');
  }

  public async function testNestedWithNonAsyncChild(): Awaitable<void> {
    $xhp = <async:test><b>BE BOLD</b></async:test>;
    expect(await $xhp->toStringAsync())->toEqual('<div><b>BE BOLD</b></div>');
  }

  public function parallelizationContainersProvider(): varray<varray<:xhp>> {
    return varray[
      varray[<test:xfrag_wrap />],
      varray[<test:async_xfrag_wrap />],
    ];
  }

  <<DataProvider('parallelizationContainersProvider')>>
  public async function testParallelization(:x:element $container): Awaitable<void> {
    :async:par_test::$log = vec[];

    $a = <async:par_test label="a" />;
    $b = <async:par_test label="b" />;
    $c = <async:par_test label="c" />;

    $container->replaceChildren(varray[$b, $c]);

    $tree = <async:test>{$a}{$container}</async:test>;
    expect(await $tree->toStringAsync())->toEqual(
      '<div><div>a</div><div>b</div><div>c</div></div>',
    );

    $log = :async:par_test::$log;
    $by_node = dict['a' => dict[], 'b' => dict[], 'c' => dict[]];

    foreach ($log as $idx => $data) {
      list($label, $action) = $data;
      $by_node[$label][$action] = $idx;
    }

    // Math\max_byx() addition to the HSL?
    $max_start = Math\max_by($by_node, $x ==> $x['start']) as nonnull['start'];
    $min_mid = Math\min_by($by_node, $x ==> $x['mid']) as nonnull['mid'];
    $max_mid = Math\max_by($by_node, $x ==> $x['mid']) as nonnull['mid'];
    // hackfmt-ignore
    $min_finish = Math\max_by($by_node, $x ==> $x['finish']) as nonnull['finish'];

    expect($min_mid)->toBeGreaterThan(
      $max_start,
      'all should be started before any get continued',
    );
    expect($min_finish)->toBeGreaterThan(
      $max_mid,
      'all should have reached stage two before any finish',
    );
    expect($min_finish)->toBeGreaterThan(
      $max_start,
      'sanity check: all have started before any finish',
    );
  }
}
