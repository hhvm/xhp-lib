---
layout: post
title: Basic XHP Abstractions
date: '2011-02-13T23:22:00-08:00'
tags:
- xhp
tumblr_url: http://codebeforethehorse.tumblr.com/post/3288864699/basic-xhp-abstractions
---
On the surface XHP is nothing more than eye candy, but used correctly it can greatly simplify development. Creating good abstractions has always been smart programming, but it’s very difficult to do that for your HTML components without mucking up your rendering code. Enter XHP to the rescue. Here I’ll show you some basic examples of how XHP can be used to abstract out your rendering logic. These will be pretty basic, but hopefully enough to give you some ideas for your own setups.
Let’s start off with a simple abstraction to render form inputs of a basic data object. We can create an XHP element that takes the object as a parameter and returns the correct HTML input:

class :ui:data-input extends :x:element {  attribute    DataObject data @required,    string property @required;  protected function render() {    $data = $this->getAttribute(''data'');    $property = $this->getAttribute(''property'');    $input =       <input        type="text"        name={$property}        class="dataInput"        value={$data->$property}        placeholder={$data->getPropertyDesc($property)}      />;    if ($data->propertyIsRequired($property)) {      $input->addClass(''dataRequired'');    }    return $input;  }}

Now all we have to do is use a <ui:data-input /> element everywhere we want a text input for our DataObject. We can continue this abstraction out, assuming we model our DataObject well enough, to handle multiple form elements. The resulting XHP might look something like this:

class :ui:data-form-element extends :x:element {  attribute    DataObject data @required,    string property @required;  protected function render() {    $data = $this->getAttribute(''data'');    $property = $this->getAttribute(''property'');    switch ($data->getPropertyType($property)) {      case ''text'':        $element =           <input            type="text"            value={$data->$property}            placeholder={$data->getPropertyDesc($property)}          />;        break;      case ''select'':        $element = <select />;        $element->setOptions(          $data->getOptions($property),          $data->$property        );        break;      case ''checkbox'':        $element =          <input            type="checkbox"            value={$data->$property}            checked={!empty($data->$property)}          />;        break;    }    $element->setAttribute(''name'', $property);    $element->addClass(''dataInput'');    if ($data->propertyIsRequired($property)) {      $element->addClass(''dataRequired'');    }    return $element;  }}

Now you can treat all properties the same by using the <ui:data-form-element /> element in your regular HTML markup. No switching in and out of PHP, or adding any logic into your HTML blocks.
Ok, cool. For my second example, let’s take a look at a common problem facing web developers: rounded corners. If progressive enhancement isn’t an option, you will be forced to add some CSS hackery to get the look you want. You can do the same hackery for all browsers, but wouldn’t it be nice to only do it for the browsers that need it? With XHP, you can. Lets say this is the HTML that you’ve built to make your rounded corners:

<div class="rounded">   <div class="topLeftCorner"></div>  <div class="topRightCorner"></div>  <div class="bottomLeftCorner"></div>  <div class="bottomRightCorner"></div>   Content goes here... </div>

For the modern browsers, all we need is the wrapper div element with border-radius applied, but IE needs a div with a background image for each corner. You could optionally include these elements every time you use the component, or you could let XHP do that for you.

class :ui:rounded-box extends :x:element {   protected function render() {    $root =       <div class="rounded">        {$this->getChildren()}      </div>;     if (Browser::isIE()) {       $root->prependChild(        <x:frag>          <div class="topLeftCorner"></div>          <div class="topRightCorner"></div>          <div class="bottomLeftCorner"></div>          <div class="bottomRightCorner"></div>        </x:frag>       );     }     return $root;   } }

Now you’ve got only the HTML you need for each browser, and when IE9 becomes standard and you want to rely solely on border-radius, just remove the Browser::isIE() check and you’re all done for your entire site.
There you have it, some simple XHP abstractions that will take the logic out of your rendering code. In my next post, I’ll show you how XHP can be used to abstract out your CSS, essentially giving you the long-desired “CSS variables” capability.
