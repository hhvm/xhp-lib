/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\{body, div, html};
use function Facebook\FBExpect\expect;

// Please see MIGRATING.md for information on how these should be used in
// practice; please don't create/use classes as unsafe as these examples.

/* HHAST_IGNORE_ERROR[FinalOrAbstractClass]: Intentionally non-final for test purpose  */
class ExampleUnsafeRenderable implements Facebook\XHP\UnsafeRenderable {
  public function __construct(public string $htmlString) {
  }

  public async function toHTMLStringAsync(): Awaitable<string> {
    return $this->htmlString;
  }
}

/* HHAST_IGNORE_ERROR[FinalOrAbstractClass]: Intentionally non-final for test purpose  */
class ExampleVeryUnsafeRenderable
  extends ExampleUnsafeRenderable
  implements Facebook\XHP\UnsafeRenderable, Facebook\XHP\AlwaysValidChild {
}

final class ExampleUnsafeAttribute extends Facebook\XHP\UnsafeAttributeValue_DEPRECATED {
  public function __construct(public string $htmlString) {
  }

  <<__Override>>
  public function toHTMLString(): string {
    return $this->htmlString;
  }
}

final class UnsafeInterfacesTest extends Facebook\HackTest\HackTest {
  public async function testUnsafeRenderable(): Awaitable<void> {
    $x = new ExampleUnsafeRenderable('<script>lollerskates</script>');
    $xhp = <div>{$x}</div>;
    expect(await $xhp->toStringAsync())->toEqual(
      '<div><script>lollerskates</script></div>',
    );
  }

  public async function testInvalidChild(): Awaitable<void> {
    expect(async () ==> {
      $x = new ExampleUnsafeRenderable('foo');
      $xhp = <html>{$x}<body /></html>;
      await $xhp->toStringAsync(); // validate, throw exception
    })->toThrow(Facebook\XHP\InvalidChildrenException::class);
  }

  public async function testAlwaysValidChild(): Awaitable<void> {
    $x = new ExampleVeryUnsafeRenderable('foo');
    $xhp = <html>{$x}<body /></html>;
    expect(await $xhp->toStringAsync())->toEqual(
      '<html>foo<body></body></html>',
    );
  }

  public async function testUnsafeAttribute(): Awaitable<void> {
    // without using XHPUnsafeAttributeValue_DEPRECATED, each &amp; will be double-escaped as &amp;amp;
    $attr = 'foo &amp;&amp; bar';
    $xhp = <div onclick={$attr} />;
    expect(await $xhp->toStringAsync())->toEqual(
      '<div onclick="foo &amp;amp;&amp;amp; bar"></div>',
    );

    // using XHPUnsafeAttributeValue_DEPRECATED the &amp; is not double escaped
    $escaped = new ExampleUnsafeAttribute('foo &amp;&amp; bar');
    $xhp = <div />;
    $xhp->forceAttribute_DEPRECATED('onclick', $escaped);
    expect(await $xhp->toStringAsync())->toEqual(
      '<div onclick="foo &amp;&amp; bar"></div>',
    );
  }
}
