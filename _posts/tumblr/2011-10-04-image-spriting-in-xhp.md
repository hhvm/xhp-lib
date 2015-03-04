---
layout: post
title: Image Spriting in XHP
date: '2011-10-04T08:28:00-07:00'
tags:
- xhp
author: Swahvay
tumblr_url: http://codebeforethehorse.tumblr.com/post/11022211307/image-spriting-in-xhp
---
I want to share with you a quick XHP class you can build that will greatly abstract your image spriting. Image sprites are a great way to reduce the number of resources downloaded from your server, but they can be a hassle to maintain. If you already sprite your images then you might have a class that generates the styles for your images. Your API might look something like this:

ImageSprite::getSpriteHtml(ImageSprite::ICON_PHOTOS);

You can sprinkle those into your rendering and it’ll work just fine, but with XHP you can build a custom component that behaves more like an HTML img tag than a PHP class and generates your spriting code behind the scenes.
Consider the follow XHP element:

class :ui:sprite extends :x:element {  attribute :img;  attribute bool usesprite = true;  private static $_spriteMap = array(    ''/icons/apps.png''   => ''appIcon'',    ''/icons/photos.png'' => ''photoIcon'',    ''/icons/users.png''  => ''userIcon'',    ...  );  protected function render() {    $img = <img class="imageSprite" />;    $src = $this->getAttribute(''src'');    if ($this->getAttribute(''usesprite'')        && isset(self::$_spriteMap[$src])) {      $img->addClass($this->_spriteMap[$src]);      $src = ''/images/spacer.gif'';    }    $img->setAttribute(''src'', $src);    return $img;  }}

Your CSS would then look something like this:
.imageSprite {  background: url(''/icons/sprite.png'') no-repeat;  display: inline-block;  height: 16px;  width: 16px;}.appIcon {  background-position: 0 0;}.photoIcon {  background-position: 0 -16px;  height: 14px;}.userIcon {  background-position: 0 -30px;  width: 15px;}
Now you can intermix this element with your HTML and get code that looks like this:
<ul class="nave">  <li>    <a href="/apps">      <ui:sprite src="/icons/apps.png" /> Apps    </a>  </li>  <li>    <a href="/photos">      <ui:sprite src="/icons/photos.png" /> Photos    </a>  </li>  <li>    <a href="/users">      <ui:sprite src="/icons/users.png" /> Users    </a>  </li></ul>
With the XHP element set up the way it is you can even add icons to your code before you get a chance to sprite them, or conditionally turn off the spriting of any instance to use the standalone icon if you want to. Facebook uses this exact method, but automated. We have a packaging system that analyzes the icon usage on a per-page basis and builds sprite maps that match the average requirements for any given page. Engineers only ever need to know where their icons are in the directory and the spriting happens behind the scenes. In fact, the icons aren’t even sprited for up to a week after they’ve been checked into the code base to give the packager enough time to analyze their usage.
Just another way XHP lets us elegantly handle an age-old problem with web development.
