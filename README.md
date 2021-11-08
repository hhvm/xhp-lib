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

If you want a high-level XHP UI library, you might want to take a look at https://github.com/hhvm/xhp-bootstrap/

Announcements and articles are posted to [the XHP-Lib blog](https://hhvm.github.io/xhp-lib/)

## Installation

[Composer](https://getcomposer.org) is the recommended installation method. To add XHP to your project, run the following command :
```console
$ composer require facebook/xhp-lib:^3.0
```

## Simple Example

```hack
$href = 'http://www.facebook.com';
$link = <a href={$href}>Facebook</a>;
```

Take note of the syntax on line 4, this is not a string. This is the major new syntax that XHP introduces to Hack.

Anything that's in {}'s is interpreted as a full Hack expression. This differs from {}'s in double-quoted strings; double-quoted strings can only contain variables.

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

All elements in XHP are just Hack classes. Even the basic HTML elements like div and span are classes. You define an element just like you do a class, except you use a leading colon to specify that you're creating an XHP element:

```hack
class :fb:thing extends :x:element {
  ...
}
```

After we define `fb:thing` we can instantiate it with the expression `<fb:thing />`. `:x:element` is the core XHP class you should subclass from when defining an element. It will provide you all the methods you need like `appendChild`, and so on. As an `:x:element` you must define only `render()`. `render()` should always return more XHP elements. It's important to remember this rule: even elements you define yourself will return XHP elements. The only XHP elements that are allowed to return a string are elements which subclass from `:x:primitive`. The only elements which should subclass `:x:primitive` are base elements that make HTML building blocks. XHP with the core HTML library is a viable replacement for strings of markup.

You can also use the leading-colon syntax to use an XHP element where you would normally use a class name, for instance while referencing class constants or typehinting:

```hack
$constant = :fb:thing::someConstant;
```

```
function giveMeAThing(:fb:thing $thing) {
}
```

## Defining Attributes

Most elements will take some number of attributes which affect its behavior. You define attributes in an element with the `attribute` keyword.

```hack
class :fb:thing extends :x:element {
  attribute
    string title = "No Title",
    enum { "cool", "lame" } type;
}
```

Here we define two attributes, `title` and `type`. `title` is of type `string` and the default value is `"No Title"`. type is of type `enum` and has two valid values -- `"cool"` and `"lame"`. Valid types are `bool`, `int`, `array`, `string`, and `var`. You can also specify a class or element name as a type. Finally, you can put @required after the name to specify that this attribute is required for the element to render.

Note that when you extend another element you will always inherit its attributes. However, any attributes you specify with the same name will override your parent's attributes.

You can also steal another element's attributes by specifying only a tag name in a definition. The declaration `attribute :div` says that this element may accept any attribute that a div element could accept.

## Defining Element Structure

All elements have some kind of structure that they must follow. For instance, in HTML5 it is illegal for an `<input />` to appear directly inside of a `<body />` tag (it must be inside a form). XHP allows you to define a content model which documents must adhere to. This is done with the `children` keyword, which uses a syntax similar to regular expressions. Note, that unlike `attribute`, `children` may only appear once inside any class.

```hack
class :fb:thing_container extends :x:element {
  children (:fb:thing1 | :fb:thing2)*;
}
```

A children declaration supports the following postfix operators:
  - `?` : Zero or one instance
  - `*` : Zero or more instances
  - `+` : One or more instances

If no operator is specified then the declaration must be matched exactly one time. You may also use the `,` or `|` operator to combine multiple declarations into one. The `,` operator specifies a list of declarations that must appear in order, and a `|` specifies a list of declarations, of which one must match. For instance if you are defining a page layout your children declaration may look like:

```hack
  children (:fb:left_column?, :fb:content, :fb:right_column?);
```

This specifies an optional left column followed by a required content and an optional right column.

You can also use the special declarations `any` or `empty` to specify that your element can accept any elements, or no elements. If you don't specify a children declaration your parent class's declaration will be inherited. `:x:element`'s children declaration is `children any;`.

Note: The algorithm which checks adherence to a children declaration is greedy with no backtracking. For most children declarations this will make no difference, but if you're defining a complex children declaration, you should know how it works. Basically, this declaration is impossible to satisfy: `children (:fb:thing*, :fb:thing);`. The `*` postfix operator is greedy and will capture all `fb:thing`'s. After that it's impossible to match another `fb:thing`.

## Element Categories

A lot of times you may want to accept all children of a particular group, but enumerating the group starts to become unsustainable. When this happens you can define an element group and specify in your child declaration that your element is a member. Then you can reference that group in a children declaration using the % prefix.

```hack
class :fb:thing1 extends :x:element {
  category %fb:thing;
}

class :fb:thing2 extends :x:element {
  category %fb:thing;
}

class :fb:thing_container extends :x:element {
  children (%fb:thing)*;
}
```

## Asynchronous data fetching

XHP supports Hack's 'async' functionality, allowing you to build components that
efficiently fetch the data that they require:

```hack
class :async-thing extends :x:element {
  protected async function renderAsync(): Awaitable<XHPRoot> {
    $db = await AsyncMysqlClient::connect(...);
    $result = await $db->queryf(
      'SELECT id2 FROM %T WHERE id1 = %d',
      'friends',
      $this->getContext('viewer')->getUserID(),
    );

    $rows = $result->mapRowsTyped();
    $friend_ids = $rows->map($row ==> $row['id2']);
    $friend_data = await HH\Asio\mm(
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

When an XHP tree is rendered, `asyncRender()` is called for all `XHPAsync` children,
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
class :fb:thing extends :x:element {
  protected async function renderAsync(): Awaitable<XHPRoot> {
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

