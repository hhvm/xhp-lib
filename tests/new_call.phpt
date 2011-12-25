--TEST--
PHP5.4 (new thing)->call()
--FILE--
<?php
class simple {
  public function call() {
    echo 'pass';
  }
}

(new simple)->call();
--EXPECT--
pass
