--TEST--
PHP5.4 JSON array syntax
--SKIPIF--
<?php 
if (version_compare(PHP_VERSION, '5.4', '<')) exit("Skip This test is for PHP 5.5 only.");
?>
--FILE--
<?php
$a = [1, 2];
--EXPECTF--

