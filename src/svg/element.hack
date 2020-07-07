/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\SVG;

use namespace Facebook\XHP\Core as x;
use namespace Facebook\XHP\HTML;


/**
 * This is the base library of SVG elements for use in XHP. This includes all
 * non-deprecated tags and attributes. Elements in this file should stay as
 * close to spec as possible. Facebook-specific extensions should go into their
 * own elements.
 */
abstract xhp class element extends x\primitive {
  use HTML\XHPHTMLHelpers;
  use x\TagLikeRenderable;
  // These attributes are only valid when the SVG element
  // is embedded in a HTML document.
  // There is no way to specify this requirement,
  // so they are always available.
  use HTML\GlobalAttributes;
  // Always valid, even when not in an HTML document.
  use HTML\EventAttributes;

  // https://svgwg.org/svg2-draft/struct.html#TermCoreAttribute
  // ‘tabindex’, ‘autofocus’, ‘lang’ and ‘style’
  // are missing intentionally, see HTML\GlobalAttributes trait.
  attribute
    // core attributes
    string class,
    string id,
    string xml:base,
    string xml:lang,
    string xml:space,
    // https://svgwg.org/svg2-draft/styling.html#TermPresentationAttribute
    // presentation attributes common to all
    enum {
      'baseline',
      'text-bottom',
      'alphabetic',
      'ideographic',
      'middle',
      'central',
      'mathematical',
      'text-top',
      'bottom',
      'center',
      'top',
    } alignment-baseline,
    mixed baseline-shift,
    string clip-path,
    enum {'nonzero', 'evenodd'} clip-rule,
    string color,
    enum {'auto', 'sRBG', 'linearRGB'} color-interpolation,
    enum {'auto', 'sRBG', 'linearRGB'} color-interpolation-filters,
    string cursor,
    enum {'auto', 'ltr', 'rtl'} direction,
    enum {
      'inline',
      'block',
      'list-item',
      'inline-block',
      'table',
      'inline-table',
      'table-row-group',
      'table-header-group',
      'table-footer-group',
      'table-row',
      'table-column-group',
      'table-column',
      'table-cell',
      'table-caption',
      'none',
      'inherit',
    } display,
    enum {
      'auto',
      'text-bottom',
      'alphabetic',
      'ideographic',
      'middle',
      'central',
      'mathematical',
      'hanging',
      'text-top',
    } dominant-baseline,
    // "inherit" or float 0 to 1 or percentage
    mixed fill-opacity,
    enum {'nonzero', 'evenodd'} fill-rule,
    string filter,
    string flood-color,
    // float 0 to 1 or percentage
    mixed flood-opacity,
    string font-family,
    // <absolute-size>, <relative-size>, <length-percentage>
    string font-size,
    // "none"  or float
    mixed font-size-adjust,
    enum {
      'normal',
      'ultra-condensed',
      'extra-condensed',
      'condensed',
      'semi-condensed',
      'semi-expanded',
      'expanded',
      'extra-expanded',
      'ultra-expanded',
    } font-stretch,
    enum {'normal', 'italic', 'oblique'} font-style,
    string font-variant,
    enum {
      'normal',
      'bold',
      'bolder',
      'lighter',
      '100',
      '200',
      '300',
      '400',
      '500',
      '600',
      '700',
      '800',
      '900',
    } font-weight,
    enum {'auto', '0deg', '0', '90deg', '90'} glyph-orientation-vertical,
    enum {'auto', 'optimizeQuality', 'optimizeSpeed'} image-rendering,
    string letter-spacing,
    string lighting-color,
    string marker-end,
    string marker-mid,
    string marker-start,
    string mask,
    enum {'alpha', 'luminance'} mask-type,
    // "inherit" or float 0 to 1 or percentage
    mixed opacity,
    enum {'auto', 'hidden', 'inherit', 'scroll', 'visible'} overflow,
    enum {'normal', 'fill', 'stoke', 'markers'} paint-order,
    enum {
      'auto',
      'bounding-box',
      'visiblePainted',
      'visibleFill',
      'visibleStroke',
      'visible',
      'painted',
      'fill',
      'stroke',
      'all',
      'none',
    } pointer-events,
    enum {
      'auto',
      'optimizeSpeed',
      'crispEdges',
      'geometricPrecision',
    } shape-rendering,
    string stop-color,
    // "inherit" or float
    mixed stop-opacity,
    string stroke,
    string stroke-dasharray,
    // <length-percentage> or float
    mixed stroke-dashoffset,
    enum {'butt', 'round', 'square'} stroke-linecap,
    enum {'miter', 'miter-clip', 'round', 'bevel', 'arcs'} stroke-linejoin,
    float stroke-miterlimit,
    // "inherit" or float 0 to 1 or percentage
    mixed stroke-opacity,
    // <length-percentage> or float
    mixed stroke-width,
    enum {'start', 'middle', 'end'} text-anchor,
    string text-decoration,
    enum {'ellipsis', 'clip', 'visible'} text-overflow,
    enum {
      'auto',
      'optimizeSpeed',
      'optimizeLegibility',
      'geometricPrecision',
    } text-rendering,
    string transform,
    string transform-origin,
    enum {
      'normal',
      'embed',
      'isolate',
      'bidi-override',
      'isolate-override',
      'plaintext',
    } unicode-bidi,
    enum {
      'none',
      'non-scaling-stroke',
      'non-scaling-size',
      'non-rotation',
      'fixed-position',
    } vector-effect,
    enum {'visible', 'hidden', 'collapse', 'inherit'} visibility,
    enum {
      'normal',
      'pre',
      'nowrap',
      'pre-wrap',
      'break-spaces',
      'pre-line',
    } whitespace,
    string word-spacing,
    enum {'horizontal-tb', 'vertical-rl', 'vertical-lr'} writing-mode;
}
