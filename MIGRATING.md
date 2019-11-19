Ideally your entire HTML tree should be generated with XHP, however this is
often impractical when migrating an existing project to XHP.

To work around this, we provide two interfaces that allow you to embed
arbitrary HTML code at any point in the tree; using these bypasses XHPs
security and/or correctness checks, so be very careful about using them. For this
reason, we have only provided interfaces, instead of concrete implementations.

The Interfaces
==============

XHPUnsafeRenderable
-------------------

**This is incredibly dangerous!**

```PHP
interface XHPUnsafeRenderable {
  public function toHTMLString();
}
```

This marks an object as being able to provide a raw HTML string. It is up to
you to make sure that the string is safe - eg no XSS vulnerabilties, and so on.

XHPAlwaysValidChild
-------------------

This makes an object pass any child element validation rules except for
"no children". While this is less likely to lead to a security issue, it may
break the assumptions of the parent object, so should be used as little as
possible.

Usage
=====

To actually embed arbitrary HTML anywhere:

```PHP
final class POTENTIAL_XSS_SECURITY_HOLE
  implements XHPAlwaysValidChild, XHPUnsafeRenderable {
  private $html;

  public function __construct($html) {
    $this->html = $html;
  }

  public function toHTMLString() {
    return $this->html;
  }
}

// The function previously known as HTML()
function POTENTIAL_XSS_SECURITY_HOLE($html) {
  return new POTENTIAL_XSS_SECURITY_HOLE($html);
}

$xhp =
  <div>
      Hello, world!
      {POTENTIAL_XSS_SECURITY_HOLE('<b>herp derp</b>')}
  </div>;
```

We **strongly** recommend making much stricter interfaces instead - for example,
instead of writing:

```
POTENTIAL_XSS_SECURITY_HOLE(render_markdown($markdown));
```

We suggest not implementing POTENTIAL_XSS_SECURITY_HOLE at all, and instead
doing something like the following:

```PHP
// Probably don't need XHPAlwaysValidChild - this is likely to be in a <div />
// or other similarly liberal container
final class XHPMarkdown implements XHPUnsafeRenderable {
  private $markdown;
  public function __construct($markdown) {
    $this->markdown = $markdown;
  }

  public function toHTMLString() {
    return render_markdown($this->markdown);
  }
}

function xhp_markdown($markdown) {
  return new XHPMarkdown($markdown);
}
```
