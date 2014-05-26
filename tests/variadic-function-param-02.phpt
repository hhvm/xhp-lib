--TEST--
Variadic Function Call 2
--SKIPIF--
<?php 
if (version_compare(PHP_VERSION, '5.6', '<')) exit("Skip This test is for PHP 5.5 only.");
?>
--FILE--
<?php
class :x {
  public $value;
  public function getValue() { return $this->value; }
}
function variadic($a, :x ...$b) { return $b[1]->getValue(); }
$a = <x />;
$b = <x />;
$a->value = 1;
$b->value = 2;
echo variadic(null, $a, $b);
--EXPECT--
2
