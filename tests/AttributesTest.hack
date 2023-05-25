/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\div;
use type Facebook\XHP\AttributeRequiredException;
use function Facebook\FBExpect\expect;
use namespace HH\Lib\Vec;

type TMyTestShape = shape('foo' => string, 'bar' => ?string);
final xhp class test:attribute_types extends x\element {
  attribute
    string mystring,
    bool mybool,
    int myint,
    vec<int> myarray,
    stdClass myobject,
    enum {'foo', 'bar'} myenum,
    float myfloat,
    Vector<string> myvector,
    Map<string, string> mymap,
    arraykey myarraykey,
    TMyTestShape myshape,
    num mynum;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div />;
  }
}

final xhp class test:required_attributes extends x\element {
  attribute string mystring @required;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div>{$this->:mystring}</div>;
  }
}

final xhp class test:default_attributes extends x\element {
  attribute string mystring = 'mydefault',
    string data-with-initializer = 'initial',
    string data-with-late-init @lateinit,
    string data-plain;

  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    return <div>{$this->:mystring}</div>;
  }
}

final xhp class test:callable_attribute extends x\element {
  attribute
    /* HH_FIXME[2049]: callable is an invalid Hack type */
    callable foo; // unsupported in 2.0+
  <<__Override>>
  protected async function renderAsync(): Awaitable<x\node> {
    $_ = $this->getAttribute('foo');
    return <div />;
  }
}

final class EmptyTestClass {
}
final class StringableTestClass {
  public function __toString(): string {
    return __CLASS__;
  }
}

final class AttributesTest extends Facebook\HackTest\HackTest {
  public async function testValidTypes(): Awaitable<void> {
    $x =
      <test:attribute_types
        mystring="foo"
        mybool={true}
        myint={123}
        myarray={vec[1, 2, 3]}
        myobject={new stdClass()}
        myenum={'foo'}
        myfloat={1.23}
        myvector={Vector {'1', '2', '3'}}
        mymap={Map {'herp' => 'derp'}}
        myshape={shape('foo' => 'herp', 'bar' => 'derp')}
      />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testValidArrayKeys(): Awaitable<void> {
    $x = <test:attribute_types myarraykey="foo" />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:attribute_types myarraykey={123} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testValidNum(): Awaitable<void> {
    $x = <test:attribute_types mynum={123} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <test:attribute_types mynum={1.23} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testNoAttributes(): Awaitable<void> {
    expect(await (<test:attribute_types />)->toStringAsync())->toEqual(
      '<div></div>',
    );
  }

  public async function testProvidingRequiredAttributes(): Awaitable<void> {
    $x = <test:required_attributes mystring="herp" />;
    expect($x->:mystring)->toEqual('herp');
    expect(await $x->toStringAsync())->toEqual('<div>herp</div>');
  }

  public async function testOmittingRequiredAttributes(): Awaitable<void> {
    expect(() ==> {
      /*HH_FIXME[4314] Attribute :mystring is not provided*/
      $x = <test:required_attributes />;
      expect($x->:mystring)->toBeNull();
    })->toThrow(Facebook\XHP\AttributeRequiredException::class);
  }

  public async function testProvidingDefaultAttributes(): Awaitable<void> {
    $x = <test:default_attributes mystring="herp" />;
    expect($x->:mystring)->toEqual('herp');
    expect($x->:data-plain)->toBeNull();
    expect($x->:data-that-does-not-exist)->toBeNull();
    expect($x->:data-with-initializer)->toEqual('initial');
    expect(() ==> $x->:data-with-late-init)->toThrow(AttributeRequiredException::class);
    expect(await $x->toStringAsync())->toEqual('<div>herp</div>');
  }

  public async function testOmittingDefaultAttributes(): Awaitable<void> {
    $x = <test:default_attributes />;
    expect($x->:mystring)->toEqual('mydefault');
    expect(await $x->toStringAsync())->toEqual('<div>mydefault</div>');
  }

  public async function testSpecialAttributes(): Awaitable<void> {
    $x = <test:default_attributes data-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual('<div>mydefault</div>');
    $x = <test:default_attributes aria-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual('<div>mydefault</div>');

    // verify that special attributes actually render
    $x = <div data-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual(
      '<div data-idonotexist="derp"></div>',
    );
    // implicit string cast
    $x = <div data-idonotexist={123} />;
    expect(await $x->toStringAsync())->toEqual(
      '<div data-idonotexist="123"></div>',
    );
    $x = <div aria-idonotexist="derp" />;
    expect(await $x->toStringAsync())->toEqual(
      '<div aria-idonotexist="derp"></div>',
    );

    // special attributes should disappear when null, like all other attributes
    $x = <div data-idonotexist={null} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');
    $x = <div aria-idonotexist={null} />;
    expect(await $x->toStringAsync())->toEqual('<div></div>');

    $x = <div data-foo="derp" />;
    $x->setAttribute('data-foo', null);
    expect(await $x->toStringAsync())->toEqual('<div></div>');
  }

  public async function testAttributeSpread(): Awaitable<void> {
    $x =
      <test:attribute_types
        mystring="foo"
        mybool={true}
        data-foo="bar"
        aria-foo="bar"
      />;
    $y = <test:attribute_types mystring="bar" {...$x} myint={5} />;
    $attrs = Vec\keys($y->getAttributes());
    expect($attrs)->toEqual(
      vec['mystring', 'mybool', 'data-foo', 'aria-foo', 'myint'],
    );

    expect($y->:mystring)->toEqual('foo');
    expect($y->:myint)->toEqual(5);
    expect($y->:mybool)->toEqual(true);
    expect($y->:data-foo)->toEqual('bar');
    expect($y->:aria-foo)->toEqual('bar');

    $x = <test:default_attributes />;
    $y = <test:attribute_types {...$x} />;
    expect($y->:mystring)->toEqual('mydefault');
    // make sure the default was copied, not present on this class
    expect((<test:attribute_types />)->:mystring)->toBeNull();

    $x = <test:default_attributes mystring="notthedefault" />;
    $y = <test:attribute_types {...$x} />;
    expect($y->:mystring)->toEqual('notthedefault');

    $x = <test:default_attributes />;
    $y = <test:attribute_types {...$x} mystring="foo" />;
    expect($y->:mystring)->toEqual('foo');

    $x = <test:default_attributes />;
    $y = <test:attribute_types mystring="foo" {...$x} />;
    expect($y->:mystring)->toEqual('mydefault');
  }
}
