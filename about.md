---
layout: page
title: About
permalink: /about/
---

XHP augments the syntax of PHP and Hack such that XML document fragments become
valid expressions. This allows you to use PHP or Hack as a stricter templating
engine and offers much more straightforward implementation of reusable
components.

There are two components:

 - [XHP-Lib](https://github.com/facebook/xhp-lib): This provides a basic
   class library for working with XHP. The 1.x series supports PHP5 and HHVM,
   however, the 2.x series is written in Hack, so HHVM is required.
 - [XHP-PHP5-Extension](https://github.com/facebookarchive/xhp-php5-extension):
   provides support for the syntax in PHP5. If you are using HHVM, no extension
   is neccessary - the syntax is supported by default for Hack files, and can
   be enabled for PHP5 files with the 'hhvm.enable_xhp' INI setting.
