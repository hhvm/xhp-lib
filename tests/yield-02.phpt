--TEST--
PHP5.4 Yield keyword 02
--FILE--
<?php
function yieldTest() {
  $a = 1;
  $b = 2;
  yield $a => $b;
}
foreach (yieldTest() as $c => $d) {
  echo $c;
  echo $d;
}
--EXPECT--
12