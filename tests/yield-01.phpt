--TEST--
PHP5.5 Yield keyword 01
--FILE--
<?php
function yieldTest() {
  $a = 1;
  yield $a;
}
foreach (yieldTest() as $b) {
  echo $b;
}
--EXPECT--
1