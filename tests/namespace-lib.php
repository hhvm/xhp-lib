<?php
// Extremely simple implementation of XHP client library useful primarily for
// namespace unit tests.

class :x {
  public function __construct() {
    echo '-'.__NAMESPACE__.'-';
  }
}
