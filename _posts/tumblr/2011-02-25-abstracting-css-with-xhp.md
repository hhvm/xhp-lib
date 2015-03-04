---
layout: post
title: Abstracting CSS with XHP
date: '2011-02-25T09:11:00-08:00'
tags:
- xhp
author: Swahvay
tumblr_url: http://codebeforethehorse.tumblr.com/post/3504948746/abstracting-css-with-xhp
---
A good site design uses a consistent palette and reusable styles, but the unavoidable pitfall is the developer will have to remember every classname for every color and format, or redeclare the same values for multiple CSS classes. There are many frameworks and scripts that try to simulate CSS variables to help with this problem, but they actually make the situation worse. You’ll still have to remember all the variables and you’ll also have to put them in multiple CSS classes. XHP provides a new (and perhaps the first real) solution to this problem. By creating a simple element that holds your common formatting and styles, you can both avoid having to remember all the CSS class names as well as stop duplicating the same style in multiple CSS classes.
Your XHP element will have an attribute for every reusable style on your site. These are the core styles like your colors and sizes. Let’s pretend we have these basic styles:

.blue {  color: #3b5998;}.lightBlue {  color: #edeff4;}.gray {  color: #808080;}.darkGray {  color: #333;}.bigText {  font-size: 16px;}.normalText {  font-size: 13px;}.smallText {  font-size: 10px;}

Just some basic colors and sizes for the text on our site. Now create an XHP element that will add these values for you, with enumerable attributes:

class :ui:text extends :x:element {  attribute    enum {''gray'', ''darkgray'', ''blue'', ''lightblue''} color,    enum {''small'', ''normal'', ''big''} size;  protected function render() {    $root = <div>{$this->getChildren()}</div>;    switch ($this->getAttribute(''color'')) {      case ''gray'':        $root->addClass(''gray'');        break;      case ''darkgray'':        $root->addClass(''darkGray'');        break;      case ''blue'':        $root->addClass(''blue'');        break;      case ''lightblue'':        $root->addClass(''lightBlue'');        break;    }    switch ($this->getAttribute(''size'')) {      case ''small'':        $root->addClass(''smallText'');        break;      case ''normal'':        $root->addClass(''normalText'');        break;      case ''big'':        $root->addClass(''bigText'');        break;    }    return $root;  }} 

You can extend on this to add any number of common styles on your site. Consider text-align, background-color, font-weight, etc. Also, you could conditionally return a different element by adding a displaytype attribute:

attribute enum {  ''inline'',   ''block'',   ''paragraph''} displaytype = ''block'';

Then switch over this attribute to create your $root:

switch ($this->getAttribute(''displaytype'')) {  case ''inline'':    $root = <span />;    break;  case ''block'':    $root = <div />;    break;  case ''paragraph'':    $root = <p />;    break;}$root->appendChild($this->getChildren());

It’s that easy. Facebook uses this practice for a large majority of text on its site. This served us in two huge ways. First, engineers didn’t have to remember what the standard color and size values were. Second, designers didn’t have to worry about engineers deviating from the standards. It also helped to dramatically reduce the CSS on our site because each CSS file only had to declare rules that were unique to those pieces of HTML it was styling. If we ever wanted to change the standard or add a new one, it was as easy as changing one CSS rule and adjusting the enum values if necessary.
Hopefully these last three posts have helped you envision some ways XHP can help you in your specific needs. In the next post I’ll get into a little of the nitty-gritty of how XHP works and show you how you can modify XHP’s core to add HTML5 data attribute support.
