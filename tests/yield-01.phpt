--TEST--
PHP5.5 Yield keyword 01
--SKIPIF--
<?php 
if (phpversion() < 5.5) exit("Skip This test is for PHP 5.5 only.");
?>
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