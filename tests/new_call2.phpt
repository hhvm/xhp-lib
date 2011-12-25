--TEST--
PHP5.4 new thing->call() should fail
--FILE--
<?php
class simple {
  public function call() {
    echo 'pass';
  }
}

new simple->call();
--EXPECTF--
Parse error: syntax error, unexpected T_OBJECT_OPERATOR (xhp) in %s on line %d

