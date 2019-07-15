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
 * Subclasses of :xhp:raw-pcdata-element must contain only Stringish children.
 * However, the strings will not be escaped. This is intended for tags like
 * <script> or <style> whose content is interpreted literally by the browser.
 *
 * From section 6.2 of the HTML 4.01 spec: "Although the STYLE and SCRIPT
 * elements use CDATA for their data model, for these elements, CDATA must be
 * handled differently by user agents. Markup and entities must be treated as
 * raw text and passed to the application as is. The first occurrence of the
 * character sequence "</" (end-tag open delimiter) is treated as terminating
 * the end of the s content. In valid documents, this would be the end tag for
 * the element."
 */
abstract class :xhp:raw-pcdata-element extends :xhp:pcdata-element {
  protected function stringify(): string {
    $buf = $this->renderBaseAttrs().'>';
    foreach ($this->getChildren() as $child) {
      if (!$child is string) {
        throw new XHPClassException($this, 'Child must be a string');
      }
      $buf .= $child;
    }
    $buf .= '</'.$this->tagName.'>';
    return $buf;
  }
}
