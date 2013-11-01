--TEST--
Callable attribute parsing
--FILE--
<?php
class :foo {
  attribute
    callable b;
}
echo "pass";
--EXPECT--
pass
