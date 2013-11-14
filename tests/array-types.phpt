--TEST--
Types in Array
--FILE--
<?php
class Foo {}
class :x {
  attribute
  	array<int> a,
  	array<float> b,
  	array<string> c,
  	array<bool> d,
  	array<array> e,
  	array<Foo> f,
  	array<string => int> g,
  	array<int => string> h;
}
$x = <x a={array(1)} />;
echo 'pass';
--EXPECT--
pass
