--TEST--
Types in Array
--FILE--
<?php
class Foo {}
class :x {
  attribute
    array a,
    array<int> b,
    array<float> c,
    array<string> d,
    array<bool> e,
    array<array> f,
    array<callable> g,
    array<Foo> h,
    array<string, int> i,
    array<int, string> j,
    array<array<string, int>> k;
}

echo 'pass';
--EXPECT--
pass
