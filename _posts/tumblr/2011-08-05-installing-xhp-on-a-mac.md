---
layout: post
title: Installing XHP on a Mac
date: '2011-08-05T12:18:00-07:00'
tags:
- xhp
author: Swahvay
tumblr_url: http://codebeforethehorse.tumblr.com/post/8523495262/installing-xhp-on-a-mac
---
XHP was built for Unix, and thus can run just fine on a Mac, but sometimes for whatever reason, XHP has a little trouble. Here are the steps to installation that seem to work if you’re getting unknown errors.
For Snow Leopard:
Install Xcode 3.2.6 (not 4.x)
Install Homebrew
In Terminal, run brew install git
in Terminal, run brew install re2c
Then follow the Terminal instructions below…
For Lion:
Install Xcode 4.x (see App Store for latest version)
Install Homebrew
In Terminal, run brew install git
In Terminal, run brew install re2c
Uninstall Xcode 4.x in Terminal by running: sudo /Developer/Library/uninstall-devtools -mode=all
Install Xcode 3.6.2
Then follow the Terminal instructions below…

$ git clone https://github.com/facebook/xhp.git $ cd xhp $ phpize $ ./configure $ make && make test $ sudo make install $ sudo cp /private/etc/php.ini.default /private/etc/php.ini $ sudo chmod 755 /private/etc/php.ini # Edit /private/etc/php.ini as per  https://github.com/facebook/xhp/wiki/Building-XHP $ php -r ''echo "XHP!\n"; exit; <a />;'' # XHP!

That should do it. Thanks to Timothy Yung for being the guinea pig and figuring this all out.
UPDATE: Some fixes have been made to XHP which will allow it to install with Xcode 4.x and Mac OS X Mountain Lion. It may however require you to install your own version of PHP, I’ve heard that Mac’s default instance has some issues still.
UPDATE: XHP has been added to Homebrew. You can now install XHP with PHP 5.3, 5.4, and 5.5 by using the following command structure:

brew install php55-xhp

Thanks to Cam Spiers for the help.
