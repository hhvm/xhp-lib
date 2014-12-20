--TEST--
XHP ->: Syntax
--FILE--
<?php

class :thing {
  public function __construct($attributes) {
    $this->attributes = $attributes;
  }
    
  public function getAttribute($attr) {
    return $this->attributes[$attr];
  }
}

$y = <thing foo-bar="pass"/>;
$y->prop = 'prop';
$x = <thing xhp-child={$y} />;
echo $y->:foo-bar."\n";  
echo $x->:xhp-child->prop."\n";
echo $x->:xhp-child->:foo-bar."\n";

--EXPECT--
pass
prop
pass
