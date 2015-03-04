---
layout: post
title: An Introduction to XHP
date: '2011-02-03T17:25:00-08:00'
tags:
- xhp
author: Swahvay
tumblr_url: http://codebeforethehorse.tumblr.com/post/3096387855/an-introduction-to-xhp
---
There seems to be very little on the web still about XHP. It’s an incredibly powerful tool that I think remains unused mostly because of its lack of documentation. Hopefully this will help get the ball rolling, so to speak, with adoption of XHP as the eventual defacto standard in PHP web programming, as is my opinion it should be.
Let’s start with the basics. Assuming you have XHP installed into your PHP instance (if not you may download the source here), you can now declare HTML nodes as PHP objects.

$img = <img src="spacer.gif" />;

Notice the lack of quotes around the image tag. This is not a string, but rather a PHP object. XHP will take this syntax and parse it out into the standard PHP object syntax.

$img = new __xhp_img(array(''src'' => ''spacer.gif''), null);

Here you can see a more recognizable syntax and how it translates into XHP. The first parameter into the constructor is an array of attributes, and the second is an array of children, obviously null in this case because img elements cannot have children.
So, ok. Now you might be saying “so what?” Well, I’ll tell you. There are a lot of advantages we gain from storing the HTML in objects before rendering them to the page.
Parse time validation of HTML syntax. Have you ever forgotten to close an element? Closed it with the wrong tag? Misspelled an element? Included an element where it didn’t belong? Mistyped an attribute? Well, you won’t have to worry about any of that anymore. XHP validates the syntax and structure of the entire tree on render and will throw an exception if any of the above cases are true.
Automatic XSS protection. Because all rendering to the page is done inside XHP, you will no longer have to worry about hidden XSS holes. XHP does all the escaping for you and security becomes the standard, not the exception.
Object mutation. Because these are PHP objects, you can pass them around and set and get any attribute or child element. No need to worry about complex regex pattern matching over HTML strings. Just get and set.
XML templating. Instead of writing functions to generate HTML, or switching in and out of PHP, you can build your own XHP elements and mix them in with basic HTML elements to maintain a single tree of XML representative of the generated HTML to be rendered to the page.
Let me expand on that last point, as I think it is a deceptively important feature of XHP. Take this example of some PHP generating a blog post:

<div class="blogPost"> <?php   echo ''<h3>''.$blog->getTitle().''</h3>'';   foreach ($blog->getMetaData() as $label => $value) {     echo ''<div class="meta>''.$label.'': ''.$value.''</div>'';   }   echo ''<div class="content">''.$blog->getContent().''</div>''; ?> </div>

This can be done simpler by creating your own XHP element to encapsulate the looping logic:

echo   <div class="blogPost">     <h3>{$blog->getTitle()}</h3>     <ui:blog-meta-data blog={$blog} />     <div class="content">{$blog->getContent()}</div>  </div>;

Now there’s just one block of XHP and you don’t need to worry about the logistics of how the meta data work when you output your blog post. Essentially we’ve separated logic from presentation. We can take this even further to a more useful abstraction and organize presentational sections into their own components.

echo <ui:blog-post blog={$blog} />;

This can be abstracted as high up the stack as your needs may suit you. For example, instead of looping through an array of blogs, you might have an element that does that for you.
Ok, now that I’ve shown you the basic advantages of XHP, let’s take a look at how to define these XHP components.  Like I mentioned before, XHP elements are just PHP classes with special syntax.  To tell the XHP parser that a particular class is an XHP element, simply prepend the class with a colon. You’ll then want to extend :x:element, which is the root class that holds all the public methods available to XHP elements.

class :ui:blog extends :x:element { ... }

It’s as simple as that. You may now instantiate your class as an XML node.
There are 3 new definitions inside an XHP element: attribute, children, and category. Attributes are what you’d think, but there are a lot of possible ways to define them.

class :ui:blog extends :x:element {  attribute :div;  attribute array tags;  attribute Blog blog @required;  attribute enum {''public'', ''private''} privacy = ''public'';}

In the first declaration, we are specifying another XHP class, which means we want to inherit all attributes from that class. We are not extending the class, but rather auto-declaring all of its attributes. So :ui:blog now accepts id, class, onclick, etc. as valid attributes. The second declaration shows the type definitions for attributes. You may specify any of the following types: int, float, string, bool, array, enum, and var. You may also declare object names as I have done in the third attribute declaration. Finally, to make any attribute required, simply append an @required, and you may give any attribute a default value. It is important to note that attribute required validation is done at call time. If you don’t set a required attribute, but never try to get it, no errors will be thrown.

class :fieldset extends :xhp:html-element {   children (:legend?, any*); }

Children validation is done through a simple regex pattern matching. There are three repetition symbols (“?" for zero or one, "+" for one to many, and "*" for zero to many), and three keywords ("any" for a catch all, "pcdata" for straight text or variables, "empty" to enforce no children). The example above taken from XHP’s declaration of the fieldset element is saying it allows an optional legend element followed by any number of additional children.  You can also OR children declarations together, like in the declaration for the tr element:

class :tr extends :xhp:html-element {   children (:th | :td)*; }

The final definition type you can give XHP elements is category. Categories are primarily used for children validation. Look at the category definition for the span element to see its simplest use case.

class :span extends :xhp:html-element {   children (%inline*);   category %inline; }

Here we are requiring that only inline elements are allowed inside a span element.
Finally, the last thing you will need to do to complete your XHP element, is to write its render method. render() is what is called when you echo your element to the page. You must return XHP from your render method, and it will be recursively rendered until there are just HTML elements left.  So, going back to our blog example above:

class :ui:blog extends :x:element {  attribute     Blog blog @required,     enum {''public'', ''private''} privacy = ''public'';   children empty;   protected function render() {     if ($this->getAttribute(''privacy'') == ''private'') {       return null;    }     $blog = $this->getAttribute(''blog'');    return       <div class="blogPost">        <h3>{$blog->getTitle()}</h3>        <ui:blog-meta-data blog={$blog} />        <div class="content">{$blog->getContent()}</div>      </div>;   } }

There you have it. The basics to generating XHP elements. Next I’ll talk about some best practices and get into more complex examples to show you where the syntax of XHP can really simplify development.
