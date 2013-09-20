--TEST--
XHP Comment Syntax
--FILE--
<?php
require 'lib.php';
echo <x><!--XML comment--></x>;
echo
  <x>
    <!--XML comment with new lines-->
  </x>;
echo
  <x>
    a
    <!--
      Multi-line comment
      with multiple lines
    -->
    b
    <x>
      c<!-- Nested comment -->d
    </x>
  </x>;
echo <x> <!-- Comment with some -- extras dashes --> </x>;
--EXPECT--
<x></x><x></x><x> a b <x> cd </x></x><x></x>
