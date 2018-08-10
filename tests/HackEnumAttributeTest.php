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

class :test:hack-enum-attribute extends :x:element {
  attribute TestEnum foo @required;
  protected function render(): XHPRoot {
    $foo = TestEnum::getNames()[$this->:foo];
    return <div>{$foo}</div>;
  }
}

class HackEnumAttributesTest extends PHPUnit_Framework_TestCase {
  public function setUp(): void {
    :xhp::enableAttributeValidation();
  }

  public function tearDown(): void {
    :xhp::disableAttributeValidation();
  }

  public function testValidValues(): void {
    $x = <test:hack-enum-attribute foo={TestEnum::HERP} />;
    expect($x->toString())->toBeSame('<div>HERP</div>');
    $x = <test:hack-enum-attribute foo={TestEnum::DERP} />;
    expect($x->toString())->toBeSame('<div>DERP</div>');
  }

  public function testValidRawValues(): void {
    // UNSAFE
    $x = <test:hack-enum-attribute foo={1} />;
    expect($x->toString())->toBeSame('<div>HERP</div>');
    $x = <test:hack-enum-attribute foo={2} />;
    expect($x->toString())->toBeSame('<div>DERP</div>');
  }

  /**
   * @expectedException XHPInvalidAttributeException
   */
  public function testInvalidValue(): void {
    // UNSAFE
    $x = <test:hack-enum-attribute foo={0} />;
  }
}
