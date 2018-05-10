<?hh
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

// Please see MIGRATING.md for information on how these should be used in
// practice; please don't create/use classes as unsafe as these examples.

class ExampleUnsafeRenderable implements XHPUnsafeRenderable {
  public function __construct(public string $htmlString) {
  }

  public function toHTMLString() {
    return $this->htmlString;
  }
}

class ExampleVeryUnsafeRenderable extends ExampleUnsafeRenderable
  implements XHPUnsafeRenderable, XHPAlwaysValidChild {
}

class UnsafeInterfacesTest extends PHPUnit_Framework_TestCase {
  public function testUnsafeRenderable() {
    $x = new ExampleUnsafeRenderable('<script>lollerskates</script>');
    $xhp = <div>{$x}</div>;
    $this->assertEquals(
      '<div><script>lollerskates</script></div>',
      $xhp->toString(),
    );
  }

  /**
   * @expectedException XHPInvalidChildrenException
   */
  public function testInvalidChild() {
    $x = new ExampleUnsafeRenderable('foo');
    $xhp = <html>{$x}<body /></html>;
    $xhp->toString(); // validate, throw exception
  }

  public function testAlwaysValidChild() {
    $x = new ExampleVeryUnsafeRenderable('foo');
    $xhp = <html>{$x}<body /></html>;
    $this->assertEquals('<html>foo<body></body></html>', $xhp->toString());
  }
}
