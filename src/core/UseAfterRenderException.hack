/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\Core;
use namespace HH\Lib\{C, Str, Vec};

final class UseAfterRenderException extends \InvalidOperationException {
  private vec<classname<node>> $xhpPath = vec[];

  public function __construct(string $message) {
    parent::__construct($message);
  }

  public function __viaXHPPath(classname<node> $node): void {
    $this->xhpPath = Vec\concat(vec[$node], $this->xhpPath);
  }

  public function getMessage(): string {
    if (C\is_empty($this->xhpPath)) {
      return $this->message;
    }
    return Vec\map(
      $this->xhpPath,
      $class ==> Str\strip_prefix($class, 'Facebook\\XHP\\'),
    )
      |> $this->message."\nVia XHPPath: ".Str\join($$, ' -> ').'.';
  }
}
