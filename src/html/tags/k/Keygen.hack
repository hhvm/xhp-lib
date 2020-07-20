/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

final xhp class keygen
  extends singleton
  implements
    Category\Phrase,
    Category\Flow,
    Category\Interactive {
  attribute
    string challenge,
    bool disabled,
    string form,
    string keytype,
    string name;

  protected string $tagName = 'keygen';
}
