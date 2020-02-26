<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace MyTestNS {

/** Intentionally conflicting name */
xhp class div extends :x:element {
  protected async function renderAsync(): Awaitable<\XHPRoot> {
    return <:div>
      -{static::class}-{$this->getChildren()}-/{static::class}-
    </:div>;
  }
}

xhp class divsubclass extends div {
}

xhp class divsubclass2 extends :MyTestNS:div {
}

xhp class useswithinnamespace extends :x:element  {
  protected async function renderAsync(): Awaitable<\XHPRoot> {
    return
      <:dl>
        <:dt>:div</:dt>
        <:dd><:div>content</:div></:dd>
        <:dt>div</:dt>
        <:dd><div>content</div></:dd>
        <:dt>divsubclass</:dt>
        <:dd><divsubclass>content</divsubclass></:dd>
        <:dt>divsubclass2</:dt>
        <:dd><divsubclass2>content</divsubclass2></:dd>
        <:dt>:x:frag</:dt>
        <:dd><:x:frag>foo</:x:frag></:dd>
      </:dl>;
  }
}

} // namespace MyTestNS

namespace {

use function Facebook\FBExpect\expect;
use type MyTestNS\div as aliaseddiv;
use namespace MyTestNS as AliasedNS;

class XHPNamespaceTest extends Facebook\HackTest\HackTest {
  public function testQualifiedReference(): void {
    expect((<MyTestNS:div>foo</MyTestNS:div>)->toString())
      ->toEqual('<div> -MyTestNS\\div-foo-/MyTestNS\\div- </div>');
  }

  public function testFullyQualifiedReference(): void {
    expect((<:MyTestNS:div>foo</:MyTestNS:div>)->toString())
      ->toEqual('<div> -MyTestNS\\div-foo-/MyTestNS\\div- </div>');
  }

  public function testUseType(): void {
    expect((<aliaseddiv>foo</aliaseddiv>)->toString())
      ->toEqual('<div> -MyTestNS\\div-foo-/MyTestNS\\div- </div>');
  }

  public function testUseNamespace(): void {
    expect((<AliasedNS:div>foo</AliasedNS:div>)->toString())
      ->toEqual('<div> -MyTestNS\\div-foo-/MyTestNS\\div- </div>');
  }

  public function testReferencesWithinNamespace(): void {
    expect((<MyTestNS:useswithinnamespace />)->toString())->toEqual((
      <dl>
        <dt>:div</dt>
        <dd><div>content</div></dd>
        <dt>div</dt>
        <dd><div> -MyTestNS\div-content-/MyTestNS\div- </div></dd>
        <dt>divsubclass</dt>
        <dd><div> -MyTestNS\divsubclass-content-/MyTestNS\divsubclass- </div></dd>
        <dt>divsubclass2</dt>
        <dd><div> -MyTestNS\divsubclass2-content-/MyTestNS\divsubclass2- </div></dd>
        <dt>:x:frag</dt>
        <dd>foo</dd>
      </dl>
    )->toString());
  }
}

} // namespace
