--TEST--
PHP5.5 Yield keyword 02
--SKIPIF--
<?php 
if (phpversion() < 5.5) exit("Skip This test is for PHP 5.5 only.");
?>
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