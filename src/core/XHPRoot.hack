/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

// Leaving this in the root namespace for consistency with the builtin
// XHPChild namespace

interface XHPRoot extends XHPChild {
  require extends \Facebook\XHP\Elements\Core\node;
}
