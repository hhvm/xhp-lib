--TEST--
Quotes in attribute
--FILE--
<?php
require 'lib.php';
$quote = '"';
echo <x b={$quote}>c</x>;
--EXPECT--
<x b="&quot;">c</x>
