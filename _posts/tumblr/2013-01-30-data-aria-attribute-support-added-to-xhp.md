---
layout: post
title: Data- & Aria- Attribute Support Added to XHP
date: '2013-01-30T19:47:00-08:00'
tags:
- xhp
tumblr_url: http://codebeforethehorse.tumblr.com/post/41920380130/data-aria-attribute-support-added-to-xhp
---
Last night I added data- and aria- attribute support into XHP. I baked it into :x:composable-element directly instead of relying on previous methods which only added it to :xhp:html-element. I did this for a few reasons. First, I didn’t like the idea of getAttribute() and setAttribute() not being final within :x:primitive. Secondly, if you want to build a UI framework on top of :x:element that forwards attributes, you’d need to un-final getAttribute() and setAttribute() in :x:element too, and duplicate all the logic in :xhp:html-element into your UI framework. No, I feel it’s much better to have the slightly nuanced behavior of always allowing data- and aria- attributes on XHP, even if they won’t do anything on custom :x:element extensions by default (HTML elements render them just fine).
You can download the latest source at: https://github.com/facebook/xhp.
