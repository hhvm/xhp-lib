## Changelog

#### This file tracks the changes made to XHP to make it more HTML5 compliant

The version of the HTML spec I used can be found on [whatwg](https://html.spec.whatwg.org/) and was [_Last Updated 15 June 2020_](https://github.com/whatwg/html/commit/f6cbe27c88012dbf8d912fe752e3e7247ff7d3ca).

### Changes

|                                           Message | Spec Links                                                  |
| ------------------------------------------------: | :---------------------------------------------------------- |
|                                   Added Changelog | N/A                                                         |
| Added 'autocapitalize' attribute to HTML\\element | `3.2.6 Global attributes` & `6.7.6 Autocapitalization`      |
|      Added 'autofocus' attribute to HTML\\element | `3.2.6 Global attributes` & `6.5.7 The autofocus attribute` |

### Links

Because the above table becomes unreadable in markdown once urls are added, the urls for the different codes can be found here.

- [3.2.6 Global attributes](https://html.spec.whatwg.org/#global-attributes)
- [6.5.7](https://html.spec.whatwg.org/#the-autofocus-attribute)
- [6.7.6 Autocapitalization](https://html.spec.whatwg.org/#autocapitalization)

### Footnotes

This section contains a longer explanations for changes when needed.

- I removed 'autofocus' from Button, Input, Keyget, Select, and Textarea. They have gotten it back via extending HTML\element. This attribute should be available to all HTML elements. According to the HTML spec: _The following attributes are common to and may be specified on all HTML elements_, see `3.2.6 Global attributes`.
