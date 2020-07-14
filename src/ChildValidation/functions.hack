/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\ChildValidation;

<<__Memoize>>
function any(): Any {
  return new Any();
}

function any_number_of<T as Constraint>(T $a): any_number_of<T> {
  return new any_number_of($a);
}

function any_of<T as Constraint>(T $a, T $b, T ...$rest): any_of<T> {
  return new any_of($a, $b, ...$rest);
}

function at_least_one_of<T as Constraint>(T $a): AtLeastOneOf<T> {
  return new AtLeastOneOf($a);
}

<<__Memoize>>
function category(string $c): Category {
  return new Category($c);
}

<<__Memoize>>
function empty(): None {
  return new None();
}

function of_type<<<__Enforceable>> reify T>(): OfType<T> {
  return new OfType<T>();
}

function optional<T as Constraint>(T $a): Optional<T> {
  return new Optional($a);
}

function pcdata(): PCData {
  return new PCData();
}

function sequence<T as Constraint>(T $a, T $b, T ...$rest): Sequence<T> {
  return new Sequence($a, $b, ...$rest);
}
