--TEST--
PHP5.5 Yield keyword 03
--SKIPIF--
<?php 
if (version_compare(PHP_VERSION, '5.5', '<')) exit("Skip This test is for PHP 5.5 only.");
?>
--FILE--
<?php
function yieldTest() {
  $a = yield;
  echo $a;
}
$b = yieldTest();
$b->send(1);
--EXPECT--
1