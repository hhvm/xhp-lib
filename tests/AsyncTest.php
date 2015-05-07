<?hh

class :async:test extends :x:element {
  use XHPAsync;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    return <div>{$this->getChildren()}</div>;
  }
}

class :async:par-test extends :x:element {
  use XHPAsync;

  attribute string label @required;

  public static $log = Vector { };

  protected async function asyncRender(): Awaitable<XHPRoot> {
    self::$log[] = [$this, 'start render'];
    await RescheduleWaitHandle::create(
      RescheduleWaitHandle::QUEUE_DEFAULT,
      0,
    );
    self::$log[] = [$this, 'rescheduled 1'];
    await RescheduleWaitHandle::create(
      RescheduleWaitHandle::QUEUE_DEFAULT,
      0,
    );
    self::$log[] = [$this, 'rescheduled 2'];
    return <div>{$this->:label}</div>;
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

  public function testParallelization() {
    $a = <async:par-test label="a" />;
    $b = <async:par-test label="b" />;
    $tree = <async:test>{$a}{$b}</async:test>;
    $this->assertSame('<div><div>a</div><div>b</div></div>', $tree->toString());

    $log = new Map(:async:par-test::$log);
    $this->assertSame(6, count($log));

    $max_start = 0;
    $min_rs1 = 6;
    $max_rs1 = 0;
    $min_rs2 = 6;
    $max_rs2 = 0;

    foreach ($log as $idx => $data) {
      list($obj, $what) = $data;
      switch ($what) {
        case 'start render':
          $max_start = max($max_start, $idx);
          break;
        case 'rescheduled 1':
          $min_rs1 = min($min_rs1, $idx);
          $max_rs1 = max($max_rs1, $idx);
          break;
        case 'rescheduled 2':
          $min_rs2 = min($min_rs2, $idx);
          $max_rs2 = max($max_rs2, $idx);
          break;
        default:
          $this->fail("Invalid action '".$what."'");
      }
    }

    $this->assertSame(
      1,
      $max_start,
      'both async children should start before first reschedule resumed',
    );
    $this->assertTrue(
      $min_rs1 > $max_start,
      'no reschedule wait handles should be complete before all asyncRenders '.
      'have started',
    );
    $this->assertTrue(
      $min_rs2 > $max_rs1,
      'the first round of rescheduled should all be queued before any are '.
      'complete',
    );
    $this->assertSame(5, $max_rs2, 'The last event must be a second reschedule');
  }
}
