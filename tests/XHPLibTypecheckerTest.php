<?hh

class XHPLibTypecheckerTest extends PHPUnit_Framework_TestCase {
  public function testTypecheckerPasses(): void {
    $output = array();
    $exit_code = null;
    exec('hh_server --check '.escapeshellarg(__DIR__.'/../'), $output, $exit_code);
    $this->assertSame(0, $exit_code, implode("\n", $output));
  }
}
