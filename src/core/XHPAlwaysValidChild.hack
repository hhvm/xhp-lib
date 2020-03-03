/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

/**
 * INCREDIBLY DANGEROUS: Marks an object as a valid child of *any* element,
 * ignoring any child rules.
 *
 * This is useful when migrating to XHP as it allows you to embed non-XHP
 * content, usually in combination with XHPUnsafeRenderable; see MIGRATING.md
 * for more information.
 */
interface XHPAlwaysValidChild {
}
