---
layout: post
title: Rendering ONLY Children in XHP
date: '2014-03-27T12:54:00-07:00'
tags:
- xhp
tumblr_url: http://codebeforethehorse.tumblr.com/post/80902252142/rendering-only-children-in-xhp
---
My last post, Rendering NULL in XHP, surprised a bunch of people by the use of extending :x:primitive to handle children rendering before the parent’s rendering. So I thought I’d quickly discuss another useful trick you can do by extending :x:primitive, this one deals with getting just the children from elements that alter their children before rendering.

There are a few cases where you want this to happen. For instance, Facebook has an element <ui:list>, which allows engineers to make lists with pre-defined spacing and border colors. The news feed is one of these lists. The problem we had was that we needed <ui:list> to add class names to its children because we couldn’t use CSS selectors to target direct children (specifically, the > selector, which IE6 didn’t support). So we had to add class names like .uiListSmallVerticalPadding to every child element. Keeping this logic inside <ui:list> meant we only needed to specify the spacing once and it would remain uniform over the whole list.
This works fine until we need to append more children through an AJAX request. When we load more news feed stories we need to create another <ui:list>, render it, but then remove the root element and only append its children to the existing news feed. :x:primitive to the rescue! We can use the rendering priority of :x:primitive to create an element that will let its child render first (adding class names to its children) and then remove the root.

class :render-children extends :x:primitive {  children (:xhp);  protected function stringify() {    $xhp =      <x:frag>        {$this->getFirstChild()->getChildren()}      </x:frag>;    return :xhp::renderChild($xhp);  }}

Now we’re left with the augmented children to append to the existing list. Easy peasy.
