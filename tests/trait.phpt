--TEST--
PHP5.4 Traits work
--FILE--
<?php
trait simple {
  function extra() { }
  public $var = 5;
}

class testing {
  use simple;
}

$a = new testing;
echo $a->var;
--EXPECT--
5