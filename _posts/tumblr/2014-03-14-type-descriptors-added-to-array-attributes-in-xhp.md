---
layout: post
title: Type Descriptors Added to Array Attributes in XHP
date: '2014-03-14T17:23:00-07:00'
tags:
- xhp
tumblr_url: http://codebeforethehorse.tumblr.com/post/79602499732/type-descriptors-added-to-array-attributes-in-xhp
---
A new level of validation has been added to XHP which will allow you to type-check your array attribute keys and values. What this means is that while before this change you were only able to validate attribute types (bool, int, string, etc.), now if the attribute is an array type you can validate its structure as well.
The syntax matches the syntax to Facebook’s recently open-sourced Hack language syntax:

attribute array<int> integers;

You can also specify keys:

attribute array<int, string> strings;

And you can nest array types:

attribute array<int, array<string>> arrays-of-strings;

Every attribute types is valid as the value of an array attribute (except enum and var), including the new callable attribute type. And just like PHP, only strings and ints are valid array keys. Just remember that numeric string keys will automatically be typecast into integers, so array(''123'' => 123) becomes array(123 => 123) and XHP validation will fail if you’ve specified string keys. Something to remember.
If you have any other requests or suggestions feel free to open an issue in the XHP Github project.
