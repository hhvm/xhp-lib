The parser converts XHP syntax to standard PHP code. This file documents some
parts of that conversion.

Class Names
===========

See `:xhp::element2class` and `:xhp::class2element`.

`__xhpChildrenDeclaration()`: `0`|`1`|expr
==========================================

This method returns the child validation rules; it is used by XHP-Lib to
enforce the child declarations at runtimes.

It returns:

 * `1`: the element accepts any children
 * `0`: the element accepts no children
 * expr: A more complicated restraint; see below 

expr: `array<int, mixed>`
-------------------------

```
array(
   0 => expr_type [0-3],
   1 => constraint_type,
   2 => constraint_data,
)
|
array(
  0 => expr_type [4-5],
  1 => expr,
  2 => expr,
)
```

expr_type: `int`
----------------

 * 0: single thing (`:thing`)
 * 1: any number of things (`:thing*`)
 * 2: zero or one things (`:thing?`)
 * 3: one or more things (`:thing+`)
 * 4: two things in sequence (`:athing, :anotherthing`)
 * 5: either of two things (`:athing || :anotherthing`)

constraint_type: `int`; constraint_data: `string`|expr|ignored
--------------------------------------------------------------

 * 1: any - no constraint. `constraint_data` is ignored.
 * 2: pcdata. `constraint_data` is ignored.
 * 3: specific element. `constraint_data` is a `string` class name
 * 4: category. `constraint_data` is a `string` category name
 * 5: expression. `constraint_data` is an expression.

`__xhpAttributeDeclaration()`: `array<string, array<int, mixed>>`
=================================================================

This returns a map from attribute names to declarations. Declarations match
the following:

```
array(
  0 => TYPE_STRING|TYPE_BOOL|TYPE_INTEGER|TYPE_ARRAY|TYPE_VAR|TYPE_FLOAT,
  1 => ignored,
  2 => default: ?mixed,
  3 => required: 1|0,
)
|
array(
  0 => TYPE_OBJECT,
  1 => class name: string,
  2 => default: ?mixed,
  3 => required: 1|0,
)
|
array(
  0 => TYPE_ENUM,
  1 => enum values: array<string>,
  2 => default: ?string,
  3 => required: 1|0,
)
```

These constants are currently declared in `:x:composable-element`.
