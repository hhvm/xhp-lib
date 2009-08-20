<?php
/** comment1a */ function /** comment1b */ foo_function /** comment1c */ (/** comment1d */) {}

/** comment2a */ abstract /** comment2b */ class /** comment2c */ FooClass /** comment2d */ {

  /** comment3a */ public /** comment3b */ function /** comment3c */ foo1 /** comment3d */ (/** comment3e */) {}

  /** comment4a */ abstract /** comment4b */ public /** comment4c */ function /** comment4d */ foo2 /** comment4e */ (/** comment4f */);

  /** comment5a */ public /** comment5b */ $foo3 /** comment5c */ = /** comment5d */ 1 /** comment5d */;

  /** comment6a */ public /** comment6b */ $foo4 /** comment6c */; 

  function foo5() {}
}

/** comment7a */ class /** comment7b */ BarClass /** comment7c */ extends /** comment7d */ FooClass /** comment7e */ {
  public function foo2(){}
}


function id($i){return $i;}

$expected = array(
  '/** comment1b */',
  '/** comment2d */',
  '/** comment3c */',
  '/** comment4d */',
  '/** comment5d */',
  '/** comment6c */',
  '',
  '/** comment7d */',
);
$actual = array(
  id(new ReflectionFunction('foo_function'))->getDocComment(),
  id(new ReflectionClass('FooClass'))->getDocComment(),
  id(new ReflectionMethod('FooClass', 'foo1'))->getDocComment(),
  id(new ReflectionMethod('FooClass', 'foo2'))->getDocComment(),
  id(new ReflectionProperty('FooClass', 'foo3'))->getDocComment(),
  id(new ReflectionProperty('FooClass', 'foo4'))->getDocComment(),
  id(new ReflectionMethod('FooClass', 'foo5'))->getDocComment(),
  id(new ReflectionClass('BarClass'))->getDocComment(),
);

foreach ($expected as $key => $val) {
  if ($val != $actual[$key]) {
    echo 'Expected: '.$val.', got '.$actual[$key]."\n";
  }
}

exit;
<a />; // I am XHP!
