---
layout: post
title: Contexts Added to XHP
date: '2014-04-14T18:25:00-07:00'
tags:
- xhp
author: Swahvay
tumblr_url: http://codebeforethehorse.tumblr.com/post/82745109442/contexts-added-to-xhp
---
I just added a new feature to XHP to allow you pass data automatically through the hierarchy of an XHP tree being rendered. That’s kind of a mouthful, but what it means is that you can set context (which is just a map of key/value pairs) on some parent element, and that context will be available on all rendered elements and their children. Let’s take a look at some examples to better understand where this would be useful.

Let’s say you have a comment section on your blog. When you are on a permalink you want the comments to be expanded, but on the feed view you only want the counts exposed with an input field. You could create an attribute to pass your view into the component and it would work just fine. The problem lies in how you’re going to get that attribute all the way into your comment component. Your comments might reside inside a feedback form (which also holds likes and shares), which itself resides in a blog post, which might reside within a blog post list, which resides within your main column content. Only your comment component needs that “page type” attribute, but now you’re going to have to add it to each one of these parent components to pass it down the tree. Bummer.
Context to the rescue! Think of XHP contexts as arbitrary attributes that get automatically forwarded to rendered components and children. You can set a value at the page-level (or any root element for that matter) and every element inside that tree will have access to the value. Let’s look at an implementation of our blog comments example above.

class :blog:comments extends :x:element {  attribute array<Comment> comments = array();  protected function render() {    $comments = $this->getAttribute(''comments'');    $commentsXHP = <x:frag />;    if ($this->getContext(''pagetype'') == ''permalink'') {      foreach ($comments as $comment) {        $commentsXHP->appendChild(          <blog:single-comment comment={$comment} />        );      }    } else {      $count = count($comments);      $commentsXHP->appendChild(        $count.'' comment''.($count != 1 ? ''s'' : '''')      );    }    $commentsXHP->appendChild(      <blog:comment-field />    );    return $commentsXHP;  }}

Notice the $this->getContext(''pagetype'') check? That value can be set on any element that would render this element or a parent of this element. So your XHP might look something like this:

// XHP Tree<blog:two-column-layout>  <blog:homepage-column>    <blog:recent-posts count={10} />  </blog:homepage-column>  <blog:nav-column /></blog:two-column-layout>// Class Definitionclass :blog:homepage-column extends :x:element {  protected function render() {    $this->setContext(''pagetype'', ''homepage'');    return      <div class="blogHomepage">        {$this->getChildren()}      </div>;  }}

That pagetype context that is set inside :blog:homepage-column will be set into :blog:recent-posts, which in turn will set it into each :blog:post it creates and so on and so forth until :blog:comments are created.
It’s important to note that this transferring only happens when rendering components. So the context will not be immediately available on children until the XHP tree is being rendered. Also of note is there is a method getAllContexts() if you would like to get an array of all contexts available on a component. Finally, you can include a default value when requesting a context by passing in a second argument:

$this->getContext(''pagetype'', ''unknown-page'');
