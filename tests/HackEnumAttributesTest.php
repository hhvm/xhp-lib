<?hh // partial
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

class :test:hack-enum-attribute extends :x:element {
  attribute TestEnum foo @required;
  protected function render(): XHPRoot {
    $foo = TestEnum::getNames()[$this->:foo];
    return <div>{$foo}</div>;
  }
}

class HackEnumAttributesTest extends Facebook\HackTest\HackTest {
  public async function beforeEachTestAsync(): Awaitable<void> {
    :xhp::enableAttributeValidation();
  }

  public async function afterEachTestAsync(): Awaitable<void> {
    :xhp::disableAttributeValidation();
  }

  public function testValidValues(): void {
    $x = <test:hack-enum-attribute foo={TestEnum::HERP} />;
    expect($x->toString())->toEqual('<div>HERP</div>');
    $x = <test:hack-enum-attribute foo={TestEnum::DERP} />;
    expect($x->toString())->toEqual('<div>DERP</div>');
  }

  public function testValidRawValues(): void {
    // UNSAFE
    $x =
      <test:hack-enum-attribute
        foo={/* HH_IGNORE_ERROR[4110] */ /* HH_IGNORE_ERROR[4343] */ 1}
      />;
    expect($x->toString())->toEqual('<div>HERP</div>');
    $x =
      <test:hack-enum-attribute
        foo={/* HH_IGNORE_ERROR[4110] *//* HH_IGNORE_ERROR[4343] */2}
      />;
    expect($x->toString())->toEqual('<div>DERP</div>');
  }

  public function testInvalidValue(): void {
    expect(() ==> {
      $x =
        <test:hack-enum-attribute
          foo={/* HH_FIXME[4110] */ /* HH_FIXME[4343] */ 0}
        />;
    })->toThrow(XHPInvalidAttributeException::class);
  }
}
