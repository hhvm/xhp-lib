--TEST--
Variadic Function Call 3
--SKIPIF--
<?php 
if (version_compare(PHP_VERSION, '5.6', '<')) exit("Skip This test is for PHP 5.5 only.");
?>
--FILE--
<?php
class :x {}
function variadic($a, $b, $c) { return $c; }
$b = [2, 3];
echo variadic(1, ...$b);
--EXPECT--
3
