<?hh

class :async:test extends :x:element {
  use XHPAsync;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <div>{$this->getChildren()}</div>;
  }
}

class :test:xfrag-wrap extends :x:element {

  protected function render(): XHPRoot {
    return <x:frag>{$this->getChildren()}</x:frag>;
  }
}

class :test:async-xfrag-wrap extends :x:element {
  use XHPAsync;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <x:frag>{$this->getChildren()}</x:frag>;
  }
}

class :async:par-test extends :x:element {
  use XHPAsync;

  attribute string label @required;

  public static $log = Vector { };

  protected async function asyncRender(): Awaitable<XHPRoot> {
    $label = $this->:label;
    self::$log[] = [$label, 'start'];
    await RescheduleWaitHandle::create(
      RescheduleWaitHandle::QUEUE_DEFAULT,
      0,
    );
    self::$log[] = [$label, 'mid'];
    await RescheduleWaitHandle::create(
      RescheduleWaitHandle::QUEUE_DEFAULT,
      0,
    );
    self::$log[] = [$label, 'finish'];
    return <div>{$label}</div>;
  }
}

class AsyncTest extends PHPUnit_Framework_TestCase {
  public function testDiv() {
    $xhp = <async:test>Herp</async:test>;
    $this->assertEquals('<div>Herp</div>', $xhp->toString());
  }

  public function testXFrag() {
    $frag = <x:frag>{1}{2}</x:frag>;
    $xhp = <async:test>{$frag}</async:test>;
    $this->assertEquals('<div>12</div>', $xhp->toString());
  }

  public function testNested() {
    $xhp = <async:test><async:test>herp derp</async:test></async:test>;
    $this->assertEquals('<div><div>herp derp</div></div>', $xhp->toString());
  }

  public function testEmpty() {
    $xhp = <async:test />;
    $this->assertEquals('<div></div>', $xhp->toString());
  }

  public function testNestedEmpty() {
    $xhp = <async:test><async:test /></async:test>;
    $this->assertEquals('<div><div></div></div>', $xhp->toString());
  }

  public function testNestedWithNonAsyncChild() {
    $xhp = <async:test><b>BE BOLD</b></async:test>;
    $this->assertEquals('<div><b>BE BOLD</b></div>', $xhp->toString());
  }

  public function testInstanceOfInterface() {
    $xhp = <async:test><b>BE BOLD</b></async:test>;
    $this->assertInstanceOf(XHPAwaitable::class, $xhp);
  }

  public function parallelizationContainersProvider() {
    return [
      [<test:xfrag-wrap />],
      [<test:async-xfrag-wrap />],
    ];
  }

  /**
   * @dataProvider parallelizationContainersProvider
   */
  public function testParallelization(:x:element $container) {
    :async:par-test::$log = Vector { };

    $a = <async:par-test label="a" />;
    $b = <async:par-test label="b" />;
    $c = <async:par-test label="c" />;

    $container->replaceChildren([$b, $c]);

    $tree = <async:test>{$a}{$container}</async:test>;
    $this->assertSame('<div><div>a</div><div>b</div><div>c</div></div>', $tree->toString());

    $log = :async:par-test::$log;
    $by_node = Map { 'a' => Map { }, 'b' => Map { }, 'c' => Map { } };

    foreach ($log as $idx => $data) {
      list($label, $action) = $data;
      $by_node[$label][$action] = $idx;
    }

    $max_start = max($by_node->map($x ==> $x['start']));
    $min_mid = min($by_node->map($x ==> $x['mid']));
    $max_mid = max($by_node->map($x ==> $x['mid']));
    $min_finish = min($by_node->map($x ==> $x['finish']));

    $this->assertGreaterThan($max_start, $min_mid, 'all should be started before any get continued');
    $this->assertGreaterThan($max_mid, $min_finish, 'all should have reached stage two before any finish');
    $this->assertGreaterThan($max_start, $min_finish, 'sanity check: all have started before any finish');
  }
}
