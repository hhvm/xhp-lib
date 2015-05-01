---
layout: post
title: New Features - In Depth
date: '2015-06-01T09:12:00-07:00'
tags: -xhp
author: fredemmott
---

XHP-Lib 2.x has included major changes and new features; this post
covers how to use them, and explains the the rationale behind some of the
decisions.

Hack Conversion
===============

XHP-Lib 2.x is written entirely in Hack, primarily so that we can take advantage
of the [async features](http://docs.hhvm.com/manual/en/hack.async.php) - though
1.x is still supported for PHP5 users. The Hack migration also means that you
can (and should) use the Hack typechecker with your XHP-based projects; this
has led to several bugs being discovered in both XHP-Lib and XHP-Bootstrap, and
many more have been prevented.

Additionally, features such as
[trait requirements](http://docs.hhvm.com/manual/en/hack.traits.requirements.php)
and traits being able to implement interfaces have both reduced the amount of
boilerplate and resulted in clearer errors for users.

Attribute Types
===============

Attribute types are now consistent with the Hack type system with the exception
of the `enum { "foo", "bar" }` syntax, which is just a `string` as far as the
typechecker is concerned; for most cases,
[hack enums](http://docs.hhvm.com/manual/en/hack.enums.details.php) are likely
to be a better choice.

This change was mostly done just to increase consistency, which reduces the
amount of rules that people need to learn; it also allows the typechecker to
verify that attributes are used correctly:

```Hack
class :foo {
  attribute
    int myattr @required;

  protected function render(): XHPRoot {
    // In all versions, the typechecker does not know the type of $untyped
    $untyped = $this->getAttribute('myattr');
    // ...but it understands that $attr is an integer (HHVM 3.6+ required)
    $attr = $this->:myattr;

    return <div />;
  }
}

function main() {
  // Correct
  $x = <foo myattr={123} />;
  /* Incorrect as this passes a string.
   *  - XHP-Lib v2.0: E_USER_DEPRECATED
   *  - XHP-Lib v2.1: exception
   *  - HHVM 3.7+: typechecker error
   */
  $x = <foo myattr="123" />;
}
```

A few points are worth highlighting:

 - Like function parameters, `string` does not allow a Stringable object. If
   you want to allow these, `Stringish` is an HHVM-specific interface supported
   by both scalar strings and by `Stringable` objects.
 - `callable` has been removed, as it is not a valid type in Hack.

Most of the HTML attributes have been converted to use `Stringish`; some
example uses include:

```Hack
$xhp = <a href={$my_uri_object} />;
$xhp = <div class={myFancyMinifyingStaticResourcesSystem('className')} />;
```

Asynchronous XHP Rendering
==========================

At Facebook, we tend to think of XHP as a component system rather than merely
a template system; this ideally means strict encapsulation, with call-sites
not aware of data-fetching requirements. For example:

```Hack
class :mysite:typeahead extends :x:element {
  attribute
    int edgetype @required;

  protected function render(): XHPRoot {
    $user = User::fetchFromID($this->getContext('userid'));
    $targets = $user->fetchRelatedObjects($this->:edgetype);
    // ...
    return <div>{ /* ... */ }</div>;
  }
}
```

Unfortunately, this code is a performance nightmare:

 - rendering this involves blocking IO - potentially 3 database queries
 - it's not obvious at call-sites that this is a very expensive component to
   render
 - the entire tree is rendered sequentially - so, every extra typeahead you ahead
   adds the time taken for 3 more database queries

Async allows us to fix this, without significantly changing the way we
structure code:

```Hack
class :mysite:typeahead extends :x:element {
  use XHPAsync;

  attribute
    int edgetype @required;

  protected async function asyncRender(): Awaitable<XHPRoot> {
    $user = await User::asyncFetchFromID($this->getContext('userid'));
    $targets = await User::asyncFetchRelatedObjects($this->:edgetype);
    return <div>{ /* ... */ }</div>;
  }
}
```

As XHP-Lib automatically parallelizes any `asyncRender()` calls in the tree, the
performance is no longer a major concern: the total IO time is the time required
for the longest data dependency chain, not the sum of all of them.

Embedding Non-XHP Content
=========================

Naively, all your markup should be XHP - however this isn't always practical
(e.g. when migrating to XHP) or desirable (e.g. if you prefer to keep static
content as markdown files). XHP-Lib now supports this natively via the
`XHPUnsafeRenderable` interface:

```Hack
class OldTemplateXHP implements XHPUnsafeRenderable {
  public function __construct(
    private OldTemplate $template,
  ) {
  }

  public function toHTMLString(): string {
    return $this->template->render();
  }
}

public function XHPIZE(OldTemplate $template): XHPChild {
  return new OldTemplateXHP($template);
}

class :my:xhp-class extends :x:element {
  protected function render(): XHPRoot {
    // ...
    $template = new MyTemplate($a, $b, $c);
    return <div>{XHPIZE($template)}</div>;
  }
}
```

There is a problem: XHP supports validating child elements, and you might need
to embed non-XHP markup in an element that validates its children. Avoid this
if at all possible, but sometimes it's not. In that case, add the
`XHPAlwaysValidChild` interface:

```Hack
class OldTemplateXHP implements XHPUnsafeRenderable, XHPAlwaysValidChild {
```

Please be extremely cautious about using either of these interfaces: their
entire purpose is to bypass the safety that XHP usually provides.

XHPHelpers
==========

We've added an additional trait, `XHPHelpers`, which solves three common
problems:

 - requiring a unique ID for an element, but not overwriting an ID if one is
   already specified - and not requiring the creator of a component to build
   support for an ID
 - transfering attributes from composite elements to the underlying HTML
   elements
 - `class` should be appended, instead of transferred verbatim

For example:

```Hack
class :example:with-id extends :x:element {
  use XHPHelpers;

  attribute :xhp:html-element;

  protected function render(): XHPRoot {
    return <div id={$this->getID()} />;
  }
}

class :example:with-transferred {
  use XHPHelpers;

  attribute :xhp:html-element;
  
  protected function render(): XHPRoot {
    return <div class="foo" />;
  }
}

function main() {
  // <div id="something_random"></div>
  var_dump((<example:with-id />)->toString());

  // <div id="herp"></div>
  var_dump((<example:with-id id="herp" />)->toString());

  // <div id="herp" class="foo"></div>
  var_dump((<example:with-transferred id="herp" />)->toString());

  // <div class="foo bar"></div>
  var_dump((<example:with-transferred class="bar" />)->toString());
}
```

The Future
==========

We feel this is a great start; we're looking forward to bringing you
[namespace support](https://github.com/facebook/xhp-lib/issues/64), and tools
to implement the 'component' concept more thoroughly.

If there are things you'd like to see, please
[file an issue on GitHub](https://github.com/facebook/xhp-lib/issues).
