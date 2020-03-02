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

enum TestEnum: int {
  HERP = 1;
  DERP = 2;
}

xhp class test:hack_enum_attribute extends :x:element {
  attribute TestEnum foo @required;
  protected async function renderAsync(): Awaitable<XHPRoot> {
    $foo = TestEnum::getNames()[$this->:foo];
    return <div>{$foo}</div>;
  }
}

class HackEnumAttributesTest extends Facebook\HackTest\HackTest {
  public async function testValidValues(): Awaitable<void> {
    $x = <test:hack_enum_attribute foo={TestEnum::HERP} />;
    expect(await $x->toStringAsync())->toEqual('<div>HERP</div>');
    $x = <test:hack_enum_attribute foo={TestEnum::DERP} />;
    expect(await $x->toStringAsync())->toEqual('<div>DERP</div>');
  }

  public async function testValidRawValues(): Awaitable<void> {
    // UNSAFE
    $x =
      <test:hack_enum_attribute
        foo={/* HH_IGNORE_ERROR[4110] */ /* HH_IGNORE_ERROR[4343] */ 1}
      />;
    expect(await $x->toStringAsync())->toEqual('<div>HERP</div>');
    $x =
      <test:hack_enum_attribute
        foo={/* HH_IGNORE_ERROR[4110] *//* HH_IGNORE_ERROR[4343] */2}
      />;
    expect(await $x->toStringAsync())->toEqual('<div>DERP</div>');
  }
}
