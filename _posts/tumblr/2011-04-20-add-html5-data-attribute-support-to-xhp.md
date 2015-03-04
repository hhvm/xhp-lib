---
layout: post
title: Add HTML5 Data Attribute Support to XHP
date: '2011-04-20T18:18:00-07:00'
tags:
- xhp
author: Swahvay
tumblr_url: http://codebeforethehorse.tumblr.com/post/4792658458/add-html5-data-attribute-support-to-xhp
---
UPDATE: I’ve added data- and aria- attribute support into XHP by default. Downloading the latest source will get you this for free.
XHP runs validation checks on all attribute sets and gets, but in the emerging world of HTML5, data attributes are validation-less. With a little bit of tweaking, you can add HTML5 data attribute support to all HTML elements in XHP. In the same swing, you can add WAI-ARIA support for your accessibility users. In this post we’ll dig into the php source of XHP and do a little optimizations of our own.
First, you’ll need to change the getAttribute() and setAttribute() functions inside :x:composable-element to account for these special attributes. The logic behind it is simple, if it’s a data or aria attribute, skip the validation checks. This is how those two functions would now look:


final public function setAttribute($attr, $val) {  if (substr($attr, 0, 5) != ''data-''       && substr($attr, 0, 5) != ''aria-'') {    $this->validateAttributeValue($attr, $val);  }  $this->attributes[$attr] = $val;  return $this;}final public function getAttribute($attr) {  if (isset($this->attributes[$attr])) {    return $this->attributes[$attr];  } else if (substr($attr, 0, 5) == ''data-''             || substr($attr, 0, 5) == ''aria-'') {    return null;  }  // Maintain the rest of this function as is.} 


Voila! Now all your XHP elements support HTML5 data attributes. You could stop here and be just fine, but technically this isn’t the best solution. HTML elements support data attributes, but you don’t want your own custom XHP components to take them*. To allow HTML5 data attributes on only HTML elements, we need to rethink our approach. Going back to XHP’s default behavior, rename the getAttribute() and setAttribute() methods in :x:composable-element to getDeclaredAttribute() and setDeclaredAttribute() respectively, make them protected, and replace them with the following non-final functions:


public function getAttribute($attr) {  return $this->getDeclaredAttribute($attr);}public function setAttribute($attr, $value) {  return $this->setDeclaredAttribute($attr, $value);} 


You’ll also need to add functions that will skip this validation to access the private $attributes array.


protected function pullAttribute($attr) {  return isset($this->attributes[$attr])     ? $this->attributes[$attr]     : null;}protected function forceAttribute($attr, $value) {  $this->attributes[$attr] = $value;} 


Now we have an over-writable base in which to skip validation. But before that we need to re-add the final keyword to :x:element so that others can’t get around the validation themselves.


final public function getAttribute($attr) {  return parent::getAttribute($attr);} final public function setAttribute($attr, $value) {  return parent::setAttribute($attr, $value);}final protected function pullAttribute($attr) {  throw new XHPClassException(    $this,     ''Cannot call pullAttribute() directly.''  );}; final protected function forceAttribute($attr, $value) {  throw new XHPClassException(    $this,     ''Cannot call forceAttribute() directly.''  );}


Now go into :xhp:html-element and add back the logic from our original implementation. Because these methods are called very often throughout the rendering of XHP, you can do a little micro-optimizations on them to help keep them slim. Add a static map of “special” attributes and do some faster checks before doing a single substr() call.


private static $specialAttrs = array(  ''data'' => true,   ''aria'' => true,);final public function setAttribute($attr, $value) {  if (isset($attr[5])      && $attr[4] == ''-''      && isset(self::$specialAttrs[substr($attr, 0, 4)])) {    $this->forceAttribute($attr, $value);  } else {    $this->setDeclaredAttribute($attr, $value);  }  return $this;}final public function getAttribute($attr) {  if (isset($attr[5])      && $attr[4] == ''-''      && isset(self::$specialAttrs[substr($attr, 0, 4)])) {    return $this->pullAttribute($attr);  } else {    return $this->getDeclaredAttribute($attr);  }}


If you wanted to be precise, you could have called parent::pullAttribute($attr) and parent::forceAttribute($attr, $value) instead of using $this, and then overwritten the methods to throw exceptions exactly like we did in :x:element, but you shouldn’t be manually extending :xhp:html-element anyways, so that’s not as important.
So there you have it. In this emerging world of Web 3.0, HTML5 data attributes are becoming increasingly popular, now you won’t be left out because you’re using a superior programming language *wink wink*.
* The reason you don’t want your own :x:element extensions supporting HTML5 data attributes is because you will not be able to set the data attribute on the return object when rendered, so it would be essentially useless unless you happen to know exactly what data attributes would be set, but then that defeats the whole point. Later I will discuss Facebook’s UI library and how we enhance :x:element extensions to automatically forward all valid (data or otherwise) attributes to a returned object from render().
