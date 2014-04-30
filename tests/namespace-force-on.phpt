--TEST--
Force Global Namespace ON
--INI--
xhp.force_global_namespace = 1
--FILE--
<?php
namespace Foo;
require 'namespace-lib.php';
<x />;
--EXPECT--
--
