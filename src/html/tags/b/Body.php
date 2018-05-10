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
    Stringish onafterprint,
    Stringish onbeforeprint,
    Stringish onbeforeunload,
    Stringish onhashchange,
    Stringish onmessage,
    Stringish onoffline,
    Stringish ononline,
    Stringish onpagehide,
    Stringish onpageshow,
    Stringish onpopstate,
    Stringish onstorage,
    Stringish onunload;
  children (pcdata | %flow)*;
  protected string $tagName = 'body';
}
