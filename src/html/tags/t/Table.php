<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :table extends :xhp:html-element {
  attribute
    int border,
    bool sortable;
  category %flow;
  children (
    :caption?,
    :colgroup*,
    :thead?,
    ((:tfoot, (:tbody+ | :tr*)) | ((:tbody+ | :tr*), :tfoot?))
  );
  protected string $tagName = 'table';
}
