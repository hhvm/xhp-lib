/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

namespace Facebook\XHP\HTML;

use namespace Facebook\XHP\Core as x;

/**
 * These attributes may exist in all HTML elements in a document.
 * However, SVG specifies that all event attributes that are valid on
 * HTML elements, are also valid on all SVG elements.
 *
 * Source: https://html.spec.whatwg.org/multipage/webappapis.html#event-handler-content-attributes
 * Source: https://svgwg.org/svg2-draft/interact.html#EventAttributes
 */
trait EventAttributes {

  attribute
    string onabort,
    string onauxclick,
    string onblur,
    string oncancel,
    string oncanplay,
    string oncanplaythrough,
    string onchange,
    string onclick,
    string onclose,
    string oncontextmenu,
    string oncopy,
    string oncuechange,
    string oncut,
    string ondblclick,
    string ondrag,
    string ondragend,
    string ondragenter,
    string ondragexit,
    string ondragleave,
    string ondragover,
    string ondragstart,
    string ondrop,
    string ondurationchange,
    string onemptied,
    string onended,
    string onerror,
    string onfocus,
    string onformdata,
    string oninput,
    string oninvalid,
    string onkeydown,
    string onkeypress,
    string onkeyup,
    string onload,
    string onloadeddata,
    string onloadedmetadata,
    string onloadstart,
    string onmousedown,
    string onmouseenter,
    string onmouseleave,
    string onmousemove,
    string onmouseout,
    string onmouseover,
    string onmouseup,
    string onmousewheel,
    string onpaste,
    string onpause,
    string onplay,
    string onplaying,
    string onprogress,
    string onratechange,
    string onreset,
    string onresize,
    string onscroll,
    string onsecuritypolicyviolation,
    string onseeked,
    string onseeking,
    string onselect,
    string onshow,
    string onslotchange,
    string onstalled,
    string onsubmit,
    string onsuspend,
    string ontimeupdate,
    string ontoggle,
    string onvolumechange,
    string onwaiting,
    string onwheel;
}
