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
use type Facebook\HackTest\DataProvider;

class :test:any-children extends :x:element {
  children any;
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:no-children extends :x:element {
  children empty;
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:single-child extends :x:element {
  children (:div);
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:optional-child extends :x:element {
  children (:div?);
  protected function render(): XHPRoot {
    return <div />;
  }
}


class :test:any-number-of-child extends :x:element {
  children (:div*);
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:at-least-one-child extends :x:element {
  children (:div+);
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:two-children extends :x:element {
  children (:div, :div);
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:either-of-two-children extends :x:element {
  children (:div | :code);
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:nested-rule extends :x:element {
  children (:div | (:code+));
  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:pcdata-child extends :x:element {
  children (pcdata);

  protected function render(): XHPRoot {
    return <div>{$this->getChildren()}</div>;
  }
}

class :test:category-child extends :x:element {
  children (%flow);

  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:has-comma-category extends :x:element {
  category %foo:bar;

  protected function render(): XHPRoot {
    return <div />;
  }
}

class :test:needs-comma-category extends :x:element {
  children (%foo:bar);

  protected function render(): XHPRoot {
    return <div />;
  }
}

class ChildRuleTest extends Facebook\HackTest\HackTest {
  public function testNoChild(): void {
    $elems = Vector {
      <test:no-children />,
      <test:any-children />,
      <test:optional-child />,
      <test:any-number-of-child />,
    };
    foreach ($elems as $elem) {
      expect($elem->__toString())->toBeSame('<div></div>');
    }
  }

  public function testUnexpectedChild(): void {
    expect(() ==> {
      $x = <test:no-children><div /></test:no-children>;
      $x->toString();
    })->toThrow(XHPInvalidChildrenException::class);
  }

  public function testSingleChild(): void {
    $elems = Vector {
      <test:any-children />,
      <test:single-child />,
      <test:optional-child />,
      <test:any-number-of-child />,
      <test:at-least-one-child />,
      <test:either-of-two-children />,
      <test:nested-rule />,
      <test:category-child />,
    };
    foreach ($elems as $elem) {
      $elem->appendChild(<div>Foo</div>);
      expect((string)$elem)->toBeSame('<div></div>');
    }
  }

  <<DataProvider('toStringProvider')>>
  public function testToString(
    :x:composable-element $elem,
    string $expected,
  ): void {
    expect($elem->__getChildrenDeclaration())->toBeSame($expected);
  }

  public function toStringProvider(): vec<(:xhp, string)> {
    return vec[
      tuple(<test:any-children />, 'any'),
      tuple(<test:no-children />, 'empty'),
      tuple(<test:single-child />, '(:div)'),
      tuple(<test:optional-child />, '(:div?)'),
      tuple(<test:any-number-of-child />, '(:div*)'),
      tuple(<test:at-least-one-child />, '(:div+)'),
      tuple(<test:two-children />, '(:div,:div)'),
      tuple(<test:either-of-two-children />, '(:div|:code)'),
      tuple(<test:nested-rule />, '(:div|(:code+))'),
      tuple(<test:pcdata-child />, '(pcdata)'),
      tuple(<test:category-child />, '(%flow)'),
    ];
  }

  public function testExpectedChild(): void {
    $elems = Vector {
      <test:single-child />,
      <test:at-least-one-child />,
      <test:either-of-two-children />,
      <test:nested-rule />,
      <test:pcdata-child />,
    };
    foreach ($elems as $elem) {
      $exception = null;
      try {
        $elem->toString();
      } catch (Exception $e) {
        $exception = $e;
      }
      expect($exception)->toBeInstanceOf(XHPInvalidChildrenException::class);
    }
  }

  public function testTooManyChildren(): void {
    $elems = Vector {
      <test:single-child />,
      <test:optional-child />,
      <test:two-children />,
      <test:either-of-two-children />,
      <test:nested-rule />,
      <test:category-child />,
    };
    foreach ($elems as $elem) {
      $exception = null;
      $elem->appendChild(<x:frag><div /><div /><div /></x:frag>);
      try {
        $elem->toString();
      } catch (Exception $e) {
        $exception = $e;
      }
      expect($exception)->toBeInstanceOf(XHPInvalidChildrenException::class);
    }
  }

  public function testIncorrectChild(): void {
    $elems = Vector {
      <test:single-child />,
      <test:optional-child />,
      <test:any-number-of-child />,
      <test:at-least-one-child />,
      <test:either-of-two-children />,
      <test:nested-rule />,
      <test:category-child />,
    };
    foreach ($elems as $elem) {
      $exception = null;
      $elem->appendChild(<thead />);
      try {
        $elem->toString();
      } catch (Exception $e) {
        $exception = $e;
      }
      expect($exception)->toBeInstanceOf(XHPInvalidChildrenException::class);
    }
  }

  public function testTwoChildren(): void {
    $elems = Vector {
      <test:any-number-of-child />,
      <test:at-least-one-child />,
      <test:two-children />,
    };
    foreach ($elems as $elem) {
      $elem->appendChild(<x:frag><div /><div /></x:frag>);
      expect($elem->toString())->toBeSame('<div></div>');
    }
  }

  public function testThreeChildren(): void {
    $elems =
      Vector { <test:any-number-of-child />, <test:at-least-one-child /> };
    foreach ($elems as $elem) {
      $elem->appendChild(<x:frag><div /><div /><div /></x:frag>);
      expect($elem->toString())->toBeSame('<div></div>');
    }
  }

  public function testEitherValidChild(): void {
    $x = <test:either-of-two-children><div /></test:either-of-two-children>;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <test:either-of-two-children><code /></test:either-of-two-children>;
    expect($x->toString())->toBeSame('<div></div>');

    $x = <test:nested-rule><div /></test:nested-rule>;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <test:nested-rule><code /></test:nested-rule>;
    expect($x->toString())->toBeSame('<div></div>');
    $x = <test:nested-rule><code /><code /></test:nested-rule>;
    expect($x->toString())->toBeSame('<div></div>');
  }

  public function testPCDataChild(): void {
    $x = <test:pcdata-child>herp derp</test:pcdata-child>;
    expect($x->toString())->toBeSame('<div>herp derp</div>');
    $x = <test:pcdata-child>{123}</test:pcdata-child>;
    expect($x->toString())->toBeSame('<div>123</div>');
  }

  public function testCommaCategory(): void {
    $x =
      <test:needs-comma-category>
        <test:has-comma-category />
      </test:needs-comma-category>;
    expect($x->toString())->toBeSame('<div></div>');
  }

  public function testFrags(): void {
    $x = <div><x:frag>{'foo'}{'bar'}</x:frag></div>;
    expect($x->toString())->toBeSame('<div>foobar</div>');
  }

  public function testNested(): void {
    expect(() ==> {
      $x = <div><test:at-least-one-child /></div>;
      $x->toString();
    })->toThrow(XHPInvalidChildrenException::class);
  }
}
