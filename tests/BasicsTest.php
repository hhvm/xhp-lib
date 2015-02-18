<?hh

class BasicsTest extends PHPUnit_Framework_TestCase {
  public function testDivWithString() {
    $xhp =
      <div>
        Hello, world.
      </div>;
    $this->assertEquals('<div> Hello, world. </div>', $xhp->toString());
  }

  public function testDivWithChild() {
    $xhp = <div><div>Herp</div></div>;
    $this->assertEquals('<div><div>Herp</div></div>', $xhp->toString());
  }

  public function testInterpolation() {
    $x = "Herp";
    $xhp = <div>{$x}</div>;
    $this->assertEquals('<div>Herp</div>', $xhp->toString());
  }

  public function testXFrag() {
    $x = 'herp';
    $y = 'derp';
    $frag = <x:frag>{$x}{$y}</x:frag>;
    $this->assertEquals(2, $frag->getChildren()->count());
    $xhp = <div>{$frag}</div>;
    $this->assertEquals('<div>herpderp</div>', $xhp->toString());
  }
}
