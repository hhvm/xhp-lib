<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

/**
 * Render an HTML conditional comment. You can choose whatever you like as
 * the conditional statement.
 */
class :x:conditional-comment extends :x:primitive {
  attribute Stringish if @required;
  children (pcdata | :xhp)*;

  protected function stringify(): string {
    $children = $this->getChildren();
    $html = '<!--[if '.(string)$this->:if.']>';
    foreach ($children as $child) {
      if ($child instanceof :xhp) {
        $html .= :xhp::renderChild($child);
      } else {
        $html .= (string)$child;
      }
    }
    $html .= '<![endif]-->';
    return $html;
  }
}
