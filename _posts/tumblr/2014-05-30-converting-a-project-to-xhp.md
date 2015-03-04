---
layout: post
title: Converting a Project to XHP
date: '2014-05-30T09:15:00-07:00'
tags:
- xhp
tumblr_url: http://codebeforethehorse.tumblr.com/post/87306947716/converting-a-project-to-xhp
---
Unless you’re starting from scratch, using XHP is most likely going to take some refactoring of old HTML-as-string code. The problem is that because of XHP’s auto-escaping to prevent XSS holes, you can’t include strings of HTML as children into XHP elements. Fortunately there’s something you can do to allow XHP to ignore certain strings and return them directly as HTML. This is essentially what Facebook had to do when we started converting our entire codebase into XHP in 2009.

First off, you’ll need a marker for strings that should be ignored by XHP. The best way to do this is to create an object that holds the strings and you can easily do instanceof checks on it. Let’s call this object HTML (protip: objects and classes exist in different contexts, so they can have the same name without problem).

class HTML {  private $htmlString;  public function __construct($htmlString) {    $this->htmlString = $htmlString;  }  public function getRawHTML() {    return $this->htmlString;  }}function HTML($htmlString) {  return new HTML($htmlString);}

Now we’ll need to adjust XHP’s internals in two places to check for the existence of HTML objects: when rendering children and when validating children. The first location will be inside :xhp:renderChild(). The method looks like this:

final protected static function renderChild($child) {  if ($child instanceof :xhp) {    return $child->__toString();  } else if (is_array($child)) {    throw new XHPRenderArrayException(''Can not render array!'');  } else {    return htmlspecialchars((string)$child);  } }

You’ll need to add a check into this block for your HTML instances. Best place is right after your check for :xhp, since that should be the most common.

final protected static function renderChild($child) {  if ($child instanceof :xhp) {    return $child->__toString();  } else if ($child instanceof HTML) {    return $child->getRawHTML();  } else if (is_array($child)) {    throw new XHPRenderArrayException(''Can not render array!'');  } else {    return htmlspecialchars((string)$child);  } }

Now your string children will render without being escaped, but we still have the problem of validating them. Unfortunately there’s no real way to mix XHP’s validation patterns with raw HTML strings, so when XHP encounters an HTML object as a child, it will need to ignore any validation checks. The function you’ll need to edit is :x:composable-element::validateChildren() and it looks like this:

final protected function validateChildren() {  $decl = $this->__xhpChildrenDeclaration();  if ($decl === 1) { // Any children allowed    return;  }  if ($decl === 0) { // No children allowed    if ($this->children) {      throw new XHPInvalidChildrenException($this, 0);    } else {      return;    }  }  $ii = 0;  if (!$this->validateChildrenExpression($decl, $ii)      || $ii < count($this->children)) {    throw new XHPInvalidChildrenException($this, $ii);  } }

At the very end before you throw an invalid children exception is where you should check for an HTML object child and return if true.

final protected function validateChildren() {  $decl = $this->__xhpChildrenDeclaration();  if ($decl === 1) { // Any children allowed    return;  }  if ($decl === 0) { // No children allowed    if ($this->children) {      throw new XHPInvalidChildrenException($this, 0);    } else {      return;    }  }  $ii = 0;  if (!$this->validateChildrenExpression($decl, $ii)      || $ii < count($this->children)) {    if (isset($this->children[$ii])        && $this->children[$ii] instanceof HTML) {      return;    }    throw new XHPInvalidChildrenException($this, $ii);  }}

And that’s it! Your XHP now supports raw HTML strings and you can slowly migrate your code to a better format.

$xhp =  <div>    {HTML(''<span>XHP and strings together!</span>'')}  </div>;

One final thing I will mention. This could also have been done with a regex function that would look at an HTML string, parse it, and then generate and return XHP objects dynamically from that string. Although doable, and in some ways better than allowing raw HTML strings in XHP, it might actually be a detriment to your code base. Since these HTML strings would be converted into XHP for you by this function, there’s less incentive to go and update them to XHP. And because they’ll need to be strings until the last moment, any new code working with them might have to be written as more HTML strings instead of XHP; and a solution that perpetuates the bad practice is only going to hurt you in the long run.
Using the HTML object instead should leave a little bit of a bad taste in your mouth and encourage you to upgrade it to XHP. Facebook went so far as to rename it to POTENTIAL_XSS_HOLE. It took time, but eventually all of Facebook’s rendering code was converted to XHP and we’ve been all the better for it.
