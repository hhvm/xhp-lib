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

class :body extends :xhp:html-element {
  attribute
    string onafterprint, string onbeforeprint, string onbeforeunload,
    string onhashchange, string onmessage, string onoffline, string ononline,
    string onpagehide, string onpageshow, string onpopstate, string onstorage,
    string onunload;
  children (pcdata | %flow)*;
  protected string $tagName = 'body';
}
