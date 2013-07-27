--TEST--
PHP5.5 Finally keyword
--SKIPIF--
<?php 
if (version_compare(PHP_VERSION, '5.5', '<')) exit("Skip This test is for PHP 5.5 only.");
?>
--FILE--
<?php
try {
  echo '1';
  throw new Exception('e');
} catch (Exception $e) {
  echo '2';	
} finally {
  echo '3';
}
--EXPECT--
123