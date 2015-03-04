---
layout: post
title: XHP Upgraded to HTML5
date: '2012-11-08T20:30:09-08:00'
tags:
- xhp
- html5
tumblr_url: http://codebeforethehorse.tumblr.com/post/35320693712/xhp-upgraded-to-html5
---
I just checked in an upgraded list of the default HTML classes in XHP that conform to the latest working draft of HTML5. This might cause some backwards compatibility issues, so I’ve also included a new public method available to all XHP elements called forceAttribute(). The method allows you to set attributes on an element and skip validation checks. I’ve also checked in a few fixes and changes to conform to the new strict standards of PHP 5.4. Please let me know if you find any issues.
You can download the latest XHP source here.
