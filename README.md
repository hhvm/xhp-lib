<p align="center"><img src="https://hhvm.github.io/xhp-lib/images/xhp_logo.png" width="350px" alt="XHP Logo"></p>

<p align="center">
  <a href="https://travis-ci.org/hhvm/xhp-lib"><img src="https://travis-ci.org/hhvm/xhp-lib.svg" alt="Build Status"></a>
  <a href="https://packagist.org/packages/facebook/xhp-lib"><img src="https://poser.pugx.org/facebook/xhp-lib/d/total.svg"></a>
  <a href="https://packagist.org/packages/facebook/xhp-lib"><img src="https://poser.pugx.org/facebook/xhp-lib/v/stable.svg"></a>
  <a href="https://packagist.org/packages/facebook/xhp-lib"><img src="https://poser.pugx.org/facebook/xhp-lib/license.svg"></a>
</p>

## Introduction

XHP augments the syntax of Hack such that XML document fragments become valid
Hack expressions. This allows you to use Hack as a stricter templating engine and
offers much more straightforward implementation of reusable components.

For a practical example of high level components you can build with xhp, you might want to take a look at the archived project [xhp-bootstrap](https://github.com/facebookarchive/xhp-bootstrap/).

Announcements and articles are posted to [The HHVM blog](https://hhvm.com/blog) and were previously posted to [the XHP-Lib blog](https://hhvm.github.io/xhp-lib/)

## Installation

[Composer](https://getcomposer.org) is the recommended installation method. To add XHP to your project, run the following command :
```console
$ composer require facebook/xhp-lib
```

## Simple Example

```hack
$href = 'http://www.facebook.com';
$link = <a href={$href}>Facebook</a>;
```

Take note of the syntax on line 2 (`$link = ...`), this is not a string. This is the major new syntax that XHP introduces to Hack. The `<a ...>` syntax is used to instantiate an object of the `a` class.

Notice the assignment to `href={$href}`. This is not string interpolation. It is setting the attribute `$link->:href`. Anything that's in {}'s is interpreted as a full Hack expression. This differs from {}'s in double-quoted strings; double-quoted strings can only contain variables.

You can define arbitrary elements that can be instantiated in Hack. Under the covers each element you create is an instance of a class. To define new elements you just define a new class. XHP comes with a set of predefined elements which implement most of HTML for you.

## Complex Structures

Note that XHP structures can be arbitrarily complex. This is a valid XHP program:

```hack
$post =
  <div class="post">
    <h2>{$post}</h2>
    <p><span>Hey there.</span></p>
    <a href={$like_link}>Like</a>
  </div>;
```

One advantage that XHP has over string construction is that it enforces correct markup structure at compile time. That is, the expression `$foo = <h1>Header</h2>;` is not a valid expression, because you can not close an `h1` tag with a `/h2`. When building large chunks of markup it can be difficult to be totally correct. With XHP the compiler now checks your work and will refuse to run until the markup is correct.

## Dynamic Structures

Sometimes it may be useful to create a bunch of elements and dynamically add them as children to an element. All XHP objects support the `appendChild` method which behaves similarly to the same Javascript method. For example:

```hack
$list = <ul />;
$items = ...;

foreach ($items as $item) {
  $list->appendChild(<li>{$item}</li>);
}
```

In the code, `<ul />` creates a ul with no children. Then we dynamically append children to it for each item in the `$items` list.

Alternatively, you can pass an array of children to `<ul>...</ul>` instead. This is especially useful when dealing with larger xhp trees where it would be harder to get a variable reference to the `ul`.

```hack
$list_items = vec[];
$items = ...;

foreach($items as $item) {
  $list_items[] = <li>{$item}</li>;
}

$list = <div><ul>{$list_items}</ul></div>;
```

## Escaping

An interesting feature of XHP is the idea of automatic escaping. If you want to render input from the user without using XHP, you must manually escape it. This practice is error-prone and has been proven over time to be an untenable solution. It increases code complexity and still leads to security vulnerabilities by careless programming. However, since XHP has context-specific about the page structure it can automatically escape data. The following two examples are identical, and both are "safe".

```hack
$hello = '<div>Hello '.htmlspecialchars($name).'</div>';
```

```
$hello = <div>Hello {$name}</div>;
```

As you can see, using XHP makes safety the default rather than the exception.

## Defining Elements

All elements in XHP are just Hack classes. Even the basic HTML elements like div and span are classes. You define an element using the `xhp` class modifier to specify that you're creating an XHP element:

```hack
use namespace Facebook\XHP\Core as x;

xhp class thing extends x\element {
  ...
}
```

Notice that we are extending `x\element`. The name `x\element` is a common shorthand for `Facebook\XHP\Core\element`. The `use` statement `use namespace Facebook\XHP\Core as x;` is commonly used in files that use xhp-lib. The use clause will be left out in future examples as `x\...` has become the canonical name for `Core` for historical reasons.

After we define `thing` we can instantiate it with the expression `<thing />`. `x\element` is the core XHP class you should subclass from when defining an element. It will provide you all the methods you need like `appendChild`, and so on. As an `x\element` you must define only `renderAsync()`. `renderAsync()` should always return more XHP elements. It's important to remember this rule: even elements you define yourself will return XHP elements. The only XHP elements that are allowed to return a string are elements which subclass from `x\primitive`. The only elements which should subclass `x\primitive` are base elements that make HTML building blocks. XHP with the core HTML library is a viable replacement for strings of markup.

## Defining Attributes

Most elements will take some number of attributes which affect its behavior. You define attributes in an element with the `attribute` keyword.

```hack
xhp class thing extends x\element {
  attribute
    string title = "No Title",
    string sub-title,
    float fill-percentage @required;
}
```

Here we define three attributes, `title`, `sub-title`, and `fill-percentage`. `title` is of type `string` and the default value is `"No Title"`. `sub-title` is of type `?string`. The attribute is optional and does not have a default value. Hack will therefore infer that `sub-title` will be `null` when you do not set it. `fill-percentage` is of type `float` and it is required. Because it is required, xhp-lib will throw during render or when accessing `$thing->:fill-percentage` if no value has been set. Hack can therefore be certain that the value will not be null.

Note that when you extend another element you will always inherit its attributes. However, any attributes you specify with the same name will override your parent's attributes.

You can also copy another element's attribute declarations by specifying only a tag name in a definition. The declaration `attribute :div` says that this element may accept any attribute that a div element could accept.

## Defining Element Structure

All elements have some kind of structure that they must follow. For instance, in HTML5 it is illegal for an `<input />` to appear directly inside of a `<body />` tag (it must be inside a form). XHP allows you to define a content model which documents must adhere to. This is done with the `XHPChild\Validation` trait. `XHPChild\Validation` is short for `Facebook\XHP\ChildValidation\Validation`. The use clause `use namespace Facebook\XHP\ChildValidation as XHPChild` is often use in files declaring xhp classes. The use clause will be left out in the examples.

```hack
xhp class thing_container extends x\element {
  abstract protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\any_number_of(
      XHPChild\any_of(
        XHPChild\of_type<thing>(),
        XHPChild\pcdata(),
      )
    );
  }
}
```

For the full list of constraints you can formulate, see the list of [ChildValidation functions](https://github.com/hhvm/xhp-lib/blob/main/src/ChildValidation/functions.hack). The example above composes the following rules. The top-level rule `any_number_of()` declares that there may be zero or more children, which all match the inner constraint. The inner constraint says that a child is valid when matches `any_of` the following contraints: It is an object of type `thing` or flat text (pcdata).

## Element Categories

A lot of times you may want to accept all children of a particular group, but enumerating the group starts to become unsustainable. When this happens you can use an interface as a marker to denote membership of a group. A good example is how all the built-in html elements implement the Category interfaces which match to the html-spec categories.

Here is an example of the category `Flow` being used in the `<audio>` element children definition.:
<!-- https://github.com/hhvm/xhp-lib/blob/d6893af6ae916dbf5e657cfc10d6d9b44bed7678/src/html/tags/a/Audio.hack#L34-L42 -->
```hack
  protected static function getChildrenDeclaration(): XHPChild\Constraint {
    return XHPChild\sequence(
      XHPChild\any_number_of(XHPChild\of_type<source>()),
      XHPChild\any_number_of(XHPChild\of_type<track>()),
      XHPChild\any_number_of(
        XHPChild\any_of(XHPChild\pcdata(), XHPChild\of_type<Category\Flow>()),
      ),
    );
  }
```

## Asynchronous data fetching

XHP supports Hack's 'async' functionality, allowing you to build components that
efficiently fetch the data that they require:

```hack
xhp class async_thing extends :x:element {
  protected async function renderAsync(): Awaitable<x\node> {
    $db = await AsyncMysqlClient::connect(...);
    $result = await $db->queryf(
      'SELECT id2 FROM %T WHERE id1 %=d',
      'friends',
      $this->getContext('viewer')->getUserID(),
    );

    $rows = $result->dictRowsTyped();
    $friend_ids = Vec\map($rows, $row ==> $row['id2']);
    $friend_data = await Vec\map_async(
      $friend_ids,
      $id ==> User::get($id),
    );

    $out = <ul />;
    foreach ($friend_ids as $id) {
      $out->appendChild(<li>.... </li>);
    }

    return $out;
  }
}
```

When an XHP tree is rendered, `renderAsync()` is called for all children,
and data fetching happens in parallel. This allows the data dependencies of
your components to efficiently be an implementation detail instead of having
to have it as part of the API and passed by the user (eg in an attribute).

## Whitespace

In XHP, text nodes that contain only whitespace are removed. The expressions `<div> </div>` and `<div />` are identical. Text nodes that contain non-whitespace are trimmed on the left and right to at most 1 space. This is worth noting because you may want to do something like:

```hack
$node = <div><label>Title:</label> <span>{$title}</span></div>;
```

This will lead to non-desirable results as the space between the `:` and `$title` will be lost. In order to fix this try moving the space into the `<label />` tag. If you can't do this then just use `{' '}` which will not be stripped.

## Best Practices

There are certain conventions that you should comply with while using XHP.

* Don't pollute the global XHP namespace with namespace-less elements. Most elements you define should use some namespace. Elements that use no namespace should not be "magic" at all. For instance,

```hack
xhp class fb:thing extends x\element {
  protected async function renderAsync(): Awaitable<x\node> {
    return <div class="thing">thing</div>;
  }
}
```

This element would be considered magic because when you print an `<fb:thing />` it actually returns a div.

## External Resources

Below are a list of external resources about XHP:

- [Code Before the Horse](http://codebeforethehorse.tumblr.com) - Basic XHP introduction, examples, and lessons learned from Facebook written by one of their UI Engineers.

## License

This software is [MIT-licensed](LICENSE).

