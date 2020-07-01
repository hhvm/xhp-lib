# IMPORTANT CLA INFORMATION

## Submitted on behalf of third-party: Scott Sandler

According to the Facebook CLA:
```
Should You wish to submit work that is not Your original creation, You may submit it to Facebook separately from any Contribution, identifying the complete details of its source and of any license or other restriction ... and conspicuously marking the work as 'Submitted on behalf of third-party: [named here].
```

## Origins of the submitted work

The Contribution on this branch is the of work from [Scott Sandler](https://github.com/ssandler).
The original was submitted to me via a Slack message.
This was prompted by [this PR comment](https://github.com/hhvm/xhp-lib/pull/260#issuecomment-645657478).
This work was given to me with the express purpose of integrating this into the `hhvm/xhp-lib` sources.
The next commit will introduce an XHP-4 compatible version of this work into the `/src/html/tags/*` directory.
The differences between `## The submitted work` and the code in `/src/html/tags/*` are my own.

## The submitted work

```HACK
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/circle
*/
final class :circle extends :svg {
	attribute
		string cx,
		string cy,
		string r;
	protected string $tagName = 'circle';
}
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/defs
*/
final class :defs extends :svg {
	protected string $tagName = 'defs';
}
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/g
*/
final class :g extends :svg {
	protected string $tagName = 'g';
}
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/mask
*/
final class :mask extends :svg {
	protected string $tagName = 'mask';
}
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/path
*/
final class :path extends :svg {
	attribute
		string d,
		int pathLength;
	protected string $tagName = 'path';
}
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/polygon
*/
final class :polygon extends :svg {
	attribute
		string points,
		num pathLength;
	protected string $tagName = 'polygon';
}
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/svg
*/
/* HHAST_FIXME[FinalOrAbstractClass] */ class :svg extends :xhp:html-element {
	attribute
		string width,
		string height,
		string viewBox,
		string version,
		string xmlns,
		string xmlns:xlink,
		num x,
		num y,
		string preserveAspectRatio,
		string clip-path,
		string clip-rule,
		string color,
		string color-interpolation,
		string color-rendering,
		string cursor,
		string display,
		string fill,
		string fill-opacity,
		string fill-rule,
		string filter,
		string mask,
		string opacity,
		string pointer-events,
		string shape-rendering,
		string stroke,
		string stroke-dasharray,
		string stroke-dashoffset,
		string stroLICENSEke-linecap,
		string stroke-linejoin,
		string stroke-miterlimit,
		string stroke-opacity,
		string stroke-width,
		string transform,
		string vector-effect,
		string visibility;
	category %phrase;
	children (pcdata | %flow | %phrase)*;
	protected string $tagName = 'svg';
}
<?hh // strict
/**
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/use
*/
final class :use extends :svg {
	attribute Stringish xlink:href;
	protected string $tagName = 'use';
}
```

### Footnote

As far as my understanding of the Facebook CLA goes, I have now done what is required in order to submit this work.
If this is not the case, please inform me, so I can correct this.
