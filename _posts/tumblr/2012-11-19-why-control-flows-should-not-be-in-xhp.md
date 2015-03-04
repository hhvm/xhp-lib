---
layout: post
title: Why Control Flows Should NOT Be In XHP
date: '2012-11-19T13:58:00-08:00'
tags:
- xhp
author: Swahvay
tumblr_url: http://codebeforethehorse.tumblr.com/post/36089777404/why-control-flows-should-not-be-in-xhp
---
About every six to nine months or so, an engineer at Facebook tries to add a control structure into XHP. These usually come in up to four flavors per diff: <x:if>, <x:switch>, <x:for>, and <x:foreach> (and occasionally <x:map>, which really is just a different <x:foreach>). A diff is submitted and invariably a long discussion ensues before the diff is eventually abandoned. I have to admit, it is tempting sometimes. I mean, we can keep everything in a single XHP block. How much cleaner is that?

$panel = userIsAdmin()  ? <ui:admin-panel />  : <ui:user-panel />;$root = <div>{$panel}</div>;
$root =  <div>    <x:if cond={userIsAdmin()}>      <ui:admin-panel />      <ui:user-panel />    </x:if>  </div>;

So much more efficient, right? Wrong! There’s a big difference between these two practices, can you think of it? Putting the conditional in XHP actually instantiates both outcomes. Because the conditions are only evaluated on render, they need to be instantiated even if they’re just going to be thrown away later. Plus, it may seem readable now, but what happens with nested statements?

<x:if cond={isLoggedIn()}>  <x:if cond={isAdmin()}>    <ui:admin-panel>    <ui:user-panel />  </x:if>  <x:if cond={canSee()}>    <div>      <ui:post />      <x:if cond={canComment()}>        <ui:comments />      </x:if>    </div>    <ui:cannot-see-content />  </x:if>  <ui:loggedout-page /></x:if>

This is getting complicated quickly. XHP is really good at giving you an abstracted view at what the generated HTML structure will be, but this completely breaks that ability. I have to parse and separate out in my head the pieces that will be rendered. But really, you’re creating tons of objects just to throw them away, that should be enough to never do this.
Ok, so that eliminates <x:if> and <x:switch>, but what about <x:for> and <x:foreach>? They won’t instantiate anything extra so we should be good, right? Well, let’s take a look at an example.

$list = <ul />;foreach ($items as $item) {  $list->appendChild(<li>{$item}</li>);}
$list =  <ul>    <x:foreach set={$items} fx={function($item) {      return <li>{$item}</li>;    }} />  </ul>;

Seems easy enough, and perhaps even beneficial to keep code in one place, but it’s important to notice that this is a fundamental shift in model. You’re creating wrapper objects to perform basic language operations. Remember that XHP is just syntactic sugar. Let’s look at what you’re really doing without the XHP syntax.

$ul = new ULElement(  new Foreach($items, function($item) {    return new LIElement($item);  }));

That seems a little sillier now. It’s needlessly complicated and just serves to duplicate a standard language construct. Furthermore, that loop is only going to be evaluated and run on render, not when it’s instantiated. So if you have objects in there, they could be augmented by the time the loop is run and your output might not be what you expect.
XHP is an extension to PHP to help with HTML rendering. It is not a language itself and should not be made to act like one. It can be very tempting — once you’ve invariably fallen in love with the XHP syntax — to want to make everything in XHP, but just remember that there is a time and a place for everything, and when it comes to control flows XHP is never the place.
