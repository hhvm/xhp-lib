<?hh // strict
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

class :body extends :xhp:html-element {
  attribute
    string onafterprint,
    string onbeforeprint,
    string onbeforeunload,
    string onhashchange,
    string onmessage,
    string onoffline,
    string ononline,
    string onpagehide,
    string onpageshow,
    string onpopstate,
    string onstorage,
    string onunload;
  children (pcdata | %flow)*;
  protected string $tagName = 'body';
}
