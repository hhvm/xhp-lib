--TEST--
XHP Basics and Entities
--FILE--
<?php 

require_once 'php-lib/core.php';
require_once 'php-lib/html.php';
define('IS_DEV_SITE', false);

function txt2html($str) {
  return htmlspecialchars($str, ENT_QUOTES, 'UTF-8');
}

echo "\n".<a>{$div = <b></b>}</a>;
--EXPECT--
<a><b></b></a>