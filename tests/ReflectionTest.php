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

use namespace Facebook\XHP\ChildValidation as XHPChild;
use namespace HH\Lib\Dict;

xhp class test:for_reflection extends :x:element {
  use XHPChildValidation;
  attribute
    string mystring @required,
    enum {'herp', 'derp'} myenum,
    string mystringwithdefault = 'mydefault';

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(XHPChild\atLeastOneOf(XHPChild\ofType<:div>()), XHPChild\optional(XHPChild\sequence(XHPChild\ofType<:code>(), XHPChild\ofType<:a>(), )), );
  }

  category %herp, %derp;

  public async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

class ReflectionTest extends Facebook\HackTest\HackTest {
  private ?ReflectionXHPClass $rxc;

  public async function beforeEachTestAsync(): Awaitable<void> {
    $this->rxc = new ReflectionXHPClass(:test:for_reflection::class);
  }

  public function testClassName(): void {
    expect($this->rxc?->getClassName())->toEqual(:test:for_reflection::class);
  }

  public function testElementName(): void {
    $name = $this->rxc?->getElementName() ?? 'NULL';
    expect(keyset['test:for-reflection', 'test:for_reflection'])->toContainKey(
      $name,
    );
  }

  public function testReflectionClass(): void {
    $rc = $this->rxc?->getReflectionClass();
    expect($rc)->toBeInstanceOf(ReflectionClass::class);
    expect($rc?->getName())->toEqual(:test:for_reflection::class);
  }

  public function testGetChildren(): void {
    $children = $this->rxc?->getChildren();
    expect($children)->toBeInstanceOf(ReflectionXHPChildrenDeclaration::class);
    expect($children?->__toString())->toEqual(':div+,(:code,:a)?');
  }

  public function testGetAttributes(): void {
    $attrs = $this->rxc?->getAttributes();
    expect($attrs)->toNotBeEmpty();
    expect(Dict\map($attrs as nonnull, ($attr ==> $attr->__toString())))
      ->toEqual(
        dict[
          'mystring' => 'string mystring @required',
          'myenum' => "enum {'herp', 'derp'} myenum",
          'mystringwithdefault' => "string mystringwithdefault = 'mydefault'",
        ],
      );
  }

  public function testGetCategories(): void {
    $categories = $this->rxc?->getCategories();
    expect($categories)->toHaveSameContentAs(Set {'herp', 'derp'});
  }
}
