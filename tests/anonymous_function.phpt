--TEST--
Anonymous Functions
--SKIPIF--
<?php 
if (version_compare(PHP_VERSION, '5.2', '<')) exit("Skip This test is for PHP 5.3 only.");
?>
--FILE--
<?php
$one = 1;
$func = function($two) use ($one) {
  return $one + $two;
};
echo $func(2);
--EXPECT--
3
