/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

/**
 * Subclasses of :xhp:pcdata_elements may contain only string children.
 */
use namespace Facebook\XHP\ChildValidation as XHPChild;

abstract xhp class pcdata_element extends element {
  use XHPChild\Validation;

  final protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\anyNumberOf(XHPChild\pcdata());
  }

}
