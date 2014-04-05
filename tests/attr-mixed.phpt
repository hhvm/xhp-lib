--TEST--
Var/Mixed attribute parsing
--FILE--
<?php
class :foo {
  attribute
    var a,
    mixed b;
}
echo "pass";
--EXPECT--
pass
