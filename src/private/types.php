<?hh
/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\_Private;

/**
 * This typehint can be flipped to keyset<T> with no internal breakages.
 * There is no (keyset<T>|ConstSet<T>) type to use.
 * Making this switch must be a BC break.
 */
type SetLike<T as arraykey> = \ConstSet<T>;
