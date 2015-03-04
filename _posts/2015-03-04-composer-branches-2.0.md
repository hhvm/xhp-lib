---
layout: post
title: Composer, Branches, and 2.0
date: '2015-03-04T11:41:00-07:00'
tags: -xhp
---

The `hack` branch of XHP-Lib is going to be merged into `master` for 2.0,
allowing cool features like
[Awaitable XHP](https://github.com/facebook/xhp-lib/pull/104) and typechecker
support for attributes and typehints (in HHVM >= 3.6).

This means that `master` is going to stop being usable in PHP5, and the `hack`
branch will stop being maintained, and eventually deleted.

If you are using Composer to install XHP-Lib:

 * Stop using `dev-master` or `dev-hack` in your composer.json as soon as
   possible
 * If you are currently using `dev-master`, switch to `1.6.*` (tagged releases)
   or `1.x-dev` (development branch)
 * If you are currently using `dev-hack`, switch to `2.x-dev`
