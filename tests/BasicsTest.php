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

class :test:renders-primitive extends :x:element {
  protected function render(): XHPRoot {
    return <x:frag><div>123</div></x:frag>;
  }
}

class BasicsTest extends PHPUnit_Framework_TestCase {
  public function testDivWithString() {
    $xhp =
      <div>
        Hello, world.
      </div>;
    expect($xhp->toString())->toBePHPEqual('<div> Hello, world. </div>');
  }

  public function testFragWithString() {
    $xhp = <x:frag>Derp</x:frag>;
    expect($xhp->toString())->toBeSame('Derp');
  }

  public function testDivWithChild() {
    $xhp = <div><div>Herp</div></div>;
    expect($xhp->toString())->toBePHPEqual('<div><div>Herp</div></div>');
  }

  public function testInterpolation() {
    $x = "Herp";
    $xhp = <div>{$x}</div>;
    expect($xhp->toString())->toBePHPEqual('<div>Herp</div>');
  }

  public function testXFrag() {
    $x = 'herp';
    $y = 'derp';
    $frag = <x:frag>{$x}{$y}</x:frag>;
    expect($frag->getChildren()->count())->toBePHPEqual(2);
    $xhp = <div>{$frag}</div>;
    expect($xhp->toString())->toBePHPEqual('<div>herpderp</div>');
  }

  public function testEscaping() {
    $xhp = <div>{"foo<SCRIPT>bar"}</div>;
    expect($xhp->toString())->toBePHPEqual('<div>foo&lt;SCRIPT&gt;bar</div>');
  }

  public function testElement2Class(): void {
    expect(:xhp::element2class('div'))->toBeSame(:div::class);
  }

  public function testClass2Element(): void {
    expect(:xhp::class2element(:div::class))->toBeSame('div');
  }

  public function testRendersPrimitive(): void {
    $xhp = <test:renders-primitive />;
    expect($xhp->toString())->toBeSame('<div>123</div>');
  }

  public function testJsonSerialize(): void {
    $xhp = <div>Hello world.</div>;
    expect(json_encode([$xhp]))->toBeSame('["<div>Hello world.<\/div>"]');
  }
}
