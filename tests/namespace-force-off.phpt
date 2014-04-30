--TEST--
Force Global Namespace OFF
--INI--
xhp.force_global_namespace = 0
--FILE--
<?php
namespace Foo;
class :x {
  public function __construct() {
    echo '-'.__NAMESPACE__.'-';
  }
}
<x />;
--EXPECT--
-Foo-
