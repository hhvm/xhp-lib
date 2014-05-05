--TEST--
Variadic Function Call 1
--SKIPIF--
<?php 
if (version_compare(PHP_VERSION, '5.6', '<')) exit("Skip This test is for PHP 5.5 only.");
?>
--FILE--
<?php
class :x {}
function variadic($a, ...$b) { return $b[1]; }
echo variadic(1, 2, 3);
--EXPECT--
3
