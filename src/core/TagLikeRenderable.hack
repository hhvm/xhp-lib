/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\Core;

use namespace Facebook\XHP\Core as x;
use namespace HH\Lib\{Str, Vec};

/**
 * This trait is meant to be used by base xhp element classes.
 * Think of `HTML\element` and SVG\element`.
 *
 * This trait implements the stringification of
 * elements which look like this:
 * ```
 * <$this->tagname ...attributes>...children</$this->tagname>
 * ```
 *
 * Some html elements look like this:
 * ```
 * <$this->tagname>
 * ```
 * These are called void elements in the html spec.
 * These elements extend `HTML\singleton` which overrides override stringifyAsync().
 */
trait TagLikeRenderable {
  require extends x\primitive;

  /**
   * Forgetting to override this value in an xhp tag is an error.
   */
  protected string $tagName = '';

  protected final function renderBaseAttrs(): string {
    $buf = '<'.$this->tagName;
    foreach ($this->getAttributes() as $key => $val) {
      if ($val !== null && $val !== false) {
        if ($val === true) {
          $buf .= ' '.\htmlspecialchars($key);
        } else {
          if ($val is \Facebook\XHP\UnsafeAttributeValue_DEPRECATED) {
            $val_str = $val->toHTMLString();
          } else {
            $val_str = \htmlspecialchars((string)$val, \ENT_COMPAT);
          }

          $buf .= ' '.\htmlspecialchars($key).'="'.$val_str.'"';
        }
      }
    }
    return $buf;
  }

  protected async function stringifyAsync(): Awaitable<string> {
    $buf = $this->renderBaseAttrs().'>';
    $buf .= await Vec\map_async(
      $this->getChildren(),
      async $child ==> await self::renderChildAsync($child),
    )
      |> Str\join($$, '');
    $buf .= '</'.$this->tagName.'>';
    return $buf;
  }
}
