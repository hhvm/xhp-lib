/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use function Facebook\FBExpect\expect;
use type Facebook\HackTest\DataProvider;
use namespace Facebook\XHP\ChildValidation as XHPChild;

xhp class test:new_child_declaration_only extends :x:element {
  use XHPChildValidation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\ofType<:div>();
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <x:frag>{$this->getChildren()}</x:frag>;
  }
}

xhp class test:new_and_old_child_declarations extends :x:element {
  // Providing all of these is invalid; for a migration consistency check, use
  // the XHPChildDeclarationConsistencyValidation trait instead.
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\ofType<:div>();
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:old_child_declaration_only extends :x:element {
  use XHPChildValidation;

  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\ofType<:div>();
  }


  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <x:frag>{$this->getChildren()}</x:frag>;
  }
}

xhp class test:any_children extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any();
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:no_children extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\empty();
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:single_child extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\ofType<:div>();
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:optional_child extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\optional(XHPChild\ofType<:div>());
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:any_number_of_child extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\ofType<:div>());
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:at_least_one_child extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\atLeastOneOf(XHPChild\ofType<:div>());
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:two_children extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(XHPChild\ofType<:div>(), XHPChild\ofType<:div>());
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:three_children extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\ofType<:div>(),
      XHPChild\ofType<:div>(),
      XHPChild\ofType<:div>(),
    );
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}


xhp class test:either_of_two_children extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyOf(XHPChild\ofType<:div>(), XHPChild\ofType<:code>());
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:any_of_three_children extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyOf(
      XHPChild\ofType<:div>(),
      XHPChild\ofType<:code>(),
      XHPChild\ofType<:p>(),
    );
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}


xhp class test:nested_rule extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyOf(
      XHPChild\ofType<:div>(),
      XHPChild\atLeastOneOf(XHPChild\ofType<:code>()),
    );
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:pcdata_child extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\pcdata();
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div>{$this->getChildren()}</div>;
  }
}

xhp class test:category_child extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\category('%flow');
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:has_comma_category extends :x:element {
  category %foo:bar;

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

xhp class test:needs_comma_category extends :x:element {
  use XHPChildValidation;
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\category('%foo:bar');
  }

  protected async function renderAsync(): Awaitable<XHPRoot> {
    return <div />;
  }
}

class ChildRuleTest extends Facebook\HackTest\HackTest {
  public async function testNoChild(): Awaitable<void> {
    $elems = vec[
      <test:no_children />,
      <test:any_children />,
      <test:optional_child />,
      <test:any_number_of_child />,
    ];
    foreach ($elems as $elem) {
      expect(await $elem->toStringAsync())->toEqual('<div></div>');
    }
  }

  public async function testUnexpectedChild(): Awaitable<void> {
    expect(async () ==> {
      $x = <test:no_children><div /></test:no_children>;
      await $x->toStringAsync();
    })->toThrow(XHPInvalidChildrenException::class);
  }

  public async function testSingleChild(): Awaitable<void> {
    $elems = vec[
      <test:any_children />,
      <test:single_child />,
      <test:optional_child />,
      <test:any_number_of_child />,
      <test:at_least_one_child />,
      <test:either_of_two_children />,
      <test:any_of_three_children />,
      <test:nested_rule />,
      <test:category_child />,
    ];
    foreach ($elems as $elem) {
      $elem->appendChild(<div>Foo</div>);
      expect(await $elem->toStringAsync())->toEqual('<div></div>');
    }
  }

  <<DataProvider('toStringProvider')>>
  public function testToString(
    :x:node $elem,
    string $expected,
  ): void {
    expect($elem->__getChildrenDeclaration())->toEqual($expected);
  }

  public function toStringProvider(): vec<(:xhp, string)> {
    return vec[
      tuple(<test:any_children />, 'any'),
      tuple(<test:no_children />, 'empty'),
      tuple(<test:single_child />, ':div'),
      tuple(<test:optional_child />, ':div?'),
      tuple(<test:any_number_of_child />, ':div*'),
      tuple(<test:at_least_one_child />, ':div+'),
      tuple(<test:two_children />, ':div,:div'),
      tuple(<test:three_children />, ':div,:div,:div'),
      tuple(<test:either_of_two_children />, ':div|:code'),
      tuple(<test:any_of_three_children />, ':div|:code|:p'),
      tuple(<test:nested_rule />, ':div|:code+'),
      tuple(<test:pcdata_child />, 'pcdata'),
      tuple(<test:category_child />, '%flow'),
    ];
  }

  public async function testExpectedChild(): Awaitable<void> {
    $elems = vec[
      <test:single_child />,
      <test:at_least_one_child />,
      <test:either_of_two_children />,
      <test:nested_rule />,
      <test:pcdata_child />,
    ];
    foreach ($elems as $elem) {
      expect(async () ==> await $elem->toStringAsync())
        ->toThrow(XHPInvalidChildrenException::class);
    }
  }

  public async function testTooManyChildren(): Awaitable<void> {
    $elems = vec[
      <test:single_child />,
      <test:optional_child />,
      <test:two_children />,
      <test:three_children />,
      <test:either_of_two_children />,
      <test:nested_rule />,
      <test:category_child />,
    ];
    foreach ($elems as $elem) {
      $exception = null;
      $elem->appendChild(<x:frag><div /><div /><div /><div /></x:frag>);
      expect(async () ==> await $elem->toStringAsync())
        ->toThrow(XHPInvalidChildrenException::class);
    }
  }

  public async function testIncorrectChild(): Awaitable<void> {
    $elems = vec[
      <test:single_child />,
      <test:optional_child />,
      <test:any_number_of_child />,
      <test:at_least_one_child />,
      <test:either_of_two_children />,
      <test:any_of_three_children />,
      <test:nested_rule />,
      <test:category_child />,
    ];
    foreach ($elems as $elem) {
      $exception = null;
      $elem->appendChild(<thead />);
      try {
        await $elem->toStringAsync();
      } catch (Exception $e) {
        $exception = $e;
      }
      expect($exception)->toBeInstanceOf(XHPInvalidChildrenException::class);
    }
  }

  public async function testTwoChildren(): Awaitable<void> {
    $elems = vec[
      <test:any_number_of_child />,
      <test:at_least_one_child />,
      <test:two_children />,
    ];
    foreach ($elems as $elem) {
      $elem->appendChild(<x:frag><div /><div /></x:frag>);
      expect(await $elem->toStringAsync())->toEqual('<div></div>');
    }
  }

  public async function testThreeChildren(): Awaitable<void> {
    $elems = vec[<test:any_number_of_child />, <test:at_least_one_child />];
    foreach ($elems as $elem) {
      $elem->appendChild(<x:frag><div /><div /><div /></x:frag>);
      expect(await $elem->toStringAsync())->toEqual('<div></div>');
    }
  }

  public async function testEitherValidChild(): Awaitable<void> {
    $x = <test:either_of_two_children><div /></test:either_of_two_children>;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:either_of_two_children><code /></test:either_of_two_children>;
    expect(await $x->toStringAsync())->toEqual('<div></div>');

    $x = <test:nested_rule><div /></test:nested_rule>;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:nested_rule><code /></test:nested_rule>;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:nested_rule><code /><code /></test:nested_rule>;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testPCDataChild(): Awaitable<void> {
    $x = <test:pcdata_child>herp derp</test:pcdata_child>;
    expect(await $x->toStringAsync())->toEqual('<div>herp derp</div>');
    $x = <test:pcdata_child>{123}</test:pcdata_child>;
    expect(await $x->toStringAsync())->toEqual('<div>123</div>');
  }

  public async function testCommaCategory(): Awaitable<void> {
    $x =
      <test:needs_comma_category>
        <test:has_comma_category />
      </test:needs_comma_category>;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testFrags(): Awaitable<void> {
    $x = <div><x:frag>{'foo'}{'bar'}</x:frag></div>;
    expect(await $x->toStringAsync())->toEqual('<div>foobar</div>');
  }

  public async function testNested(): Awaitable<void> {
    expect(async () ==> {
      $x = <div><test:at_least_one_child /></div>;
      await $x->toStringAsync();
    })->toThrow(XHPInvalidChildrenException::class);
  }

  public async function testNewChildDeclarations(): Awaitable<void> {
    expect(
      await (
        <test:new_child_declaration_only>
          <div>foo</div>
        </test:new_child_declaration_only>
      )->toStringAsync(),
    )->toEqual('<div>foo</div>');

    expect(
      async () ==> await (<test:new_child_declaration_only />)->toStringAsync(),
    )
      ->toThrow(XHPInvalidChildrenException::class);
    expect(
      async () ==> await (
        <test:new_child_declaration_only><p /></test:new_child_declaration_only>
      )->toStringAsync(),
    )->toThrow(XHPInvalidChildrenException::class);
  }

  public async function testOldChildDeclarations(): Awaitable<void> {
    expect(
      await (
        <test:old_child_declaration_only>
          <div>foo</div>
        </test:old_child_declaration_only>
      )->toStringAsync(),
    )->toEqual('<div>foo</div>');

    expect(
      async () ==> await (<test:old_child_declaration_only />)->toStringAsync(),
    )
      ->toThrow(XHPInvalidChildrenException::class);
    expect(
      async () ==> await (
        <test:old_child_declaration_only><p /></test:old_child_declaration_only>
      )->toStringAsync(),
    )->toThrow(XHPInvalidChildrenException::class);
  }
}
