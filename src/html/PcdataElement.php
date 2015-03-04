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

/**
 * Subclasses of :xhp:pcdata-elements may contain only string children.
 */
abstract class :xhp:pcdata-element extends :xhp:html-element {
  children (pcdata)*;
}
