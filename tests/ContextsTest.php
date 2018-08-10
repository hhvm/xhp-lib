<?hh
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use function Facebook\FBExpect\expect;

class :test:contexts extends :x:element {
  protected function render(): XHPRoot {
    return
      <div>
        <p>{(string)$this->getContext('heading')}</p>
        {$this->getChildren()}
      </div>;
  }
}

class XHPContextsTest extends PHPUnit_Framework_TestCase {
  public function testContextSimple(): void {
    $x = <test:contexts />;
    $x->setContext('heading', 'herp');
    expect($x->toString())->toBeSame('<div><p>herp</p></div>');
  }

  public function testContextInsideHTMLElement(): void {
    $x = <div><test:contexts /></div>;
    $x->setContext('heading', 'herp');
    expect($x->toString())->toBeSame('<div><div><p>herp</p></div></div>');
  }

  public function testNestedContexts(): void {
    $x = <test:contexts><test:contexts /></test:contexts>;
    $x->setContext('heading', 'herp');
    expect($x->toString())->toBeSame(
      '<div><p>herp</p><div><p>herp</p></div></div>',
    );
  }
}
