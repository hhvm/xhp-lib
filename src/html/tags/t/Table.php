<?hh // strict
/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

class :table extends :xhp:html-element {
  attribute int border, bool sortable;
  category %flow;
  children (
    :caption?,
    :colgroup*,
    :thead?,
    ((:tfoot, (:tbody+ | :tr*)) | ((:tbody+ | :tr*), :tfoot?))
  );
  protected string $tagName = 'table';
}
