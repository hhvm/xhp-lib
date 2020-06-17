## Changelog

#### This file tracks the changes made to XHP to make it more HTML5 compliant

The version of the HTML spec I used can be found on [whatwg](https://html.spec.whatwg.org/) and was [_Last Updated 15 June 2020_](https://github.com/whatwg/html/commit/f6cbe27c88012dbf8d912fe752e3e7247ff7d3ca).

### Changes

|                                                      Message | Spec Links                                                                                             |
| -----------------------------------------------------------: | :----------------------------------------------------------------------------------------------------- |
|                                              Added Changelog | N/A                                                                                                    |
|            Added 'autocapitalize' attribute to HTML\\element | `3.2.6 Global attributes` & `6.7.6 Autocapitalization`                                                 |
|                 Added 'autofocus' attribute to HTML\\element | `3.2.6 Global attributes` & `6.5.7 The autofocus attribute`                                            |
|              Added 'enterkeyhint' attribute to HTML\\element | `3.2.6 Global attributes` & `6.7.8 Input modalities: the enterkeyhint attribute`                       |
|                        Added 'is' attribute to HTML\\element | `3.2.6 Global attributes` & `4.13.3 Core concepts`                                                     |
|                     Added 'nonce' attribute to HTML\\element | `2.6.6 Nonce attributes` & `3.2.6 Global attributes`                                                   |
|                Added 'onauxclick' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
|                    Added 'oncopy' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
|                     Added 'oncut' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
|                Added 'onformdata' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
|                   Added 'onpaste' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
| Added 'onsecuritypolicyviolation' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
|              Added 'onslotchange' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
|                   Added 'onwheel' attribute to HTML\\element | `3.2.6 Global attributes` & `8.1.5.2 Event handlers on elements, Document objects, and Window objects` |
|                        Added 'color' attribute to HTML\\Link | `4.2.4 The link element`                                                                               |
|                     Added 'disabled' attribute to HTML\\Link | `4.2.4 The link element`                                                                               |
|                   Added 'imagesizes' attribute to HTML\\Link | `4.2.4 The link element` & `4.8.4.2.1 Srcset attributes`                                               |
|                  Added 'imagesrcset' attribute to HTML\\Link | `4.2.4 The link element` & `4.8.4.2.1 Srcset attributes`                                               |
|                    Added 'integrity' attribute to HTML\\Link | `4.2.4 The link element`                                                                               |
|               Added 'referrerpolicy' attribute to HTML\\Link | `2.6.5 Referrer policy attributes` & `4.2.4 The link element` & `Referrer Policy`                      |

### Links

Because the above table becomes unreadable in markdown once urls are added, the urls for the different codes can be found here.

- [Referrer Policy](https://w3c.github.io/webappsec-referrer-policy/)
- [2.6.5 Referrer policy attributes](https://html.spec.whatwg.org/#referrer-policy-attribute)
- [2.6.6 Nonce attributes](https://html.spec.whatwg.org/#nonce-attributes)
- [3.2.6 Global attributes](https://html.spec.whatwg.org/#global-attributes)
- [3.2.6.4 The dir attribute](https://html.spec.whatwg.org/#the-dir-attribute)
- [4.2.4 The link element](https://html.spec.whatwg.org/#the-link-element)
- [4.8.4.2.1 Srcset attributes](https://html.spec.whatwg.org/#srcset-attributes)
- [4.13.3 Core concepts](https://html.spec.whatwg.org/#custom-elements-core-concepts)
- [6.5.7 The autofocus attribute](https://html.spec.whatwg.org/#the-autofocus-attribute)
- [6.7.6 Autocapitalization](https://html.spec.whatwg.org/#autocapitalization)
- [6.7.8 Input modalities: the enterkeyhint attribute](https://html.spec.whatwg.org/#input-modalities:-the-enterkeyhint-attribute)
- [8.1.5.2 Event handlers on elements, Document objects, and Window objects](https://html.spec.whatwg.org/#event-handlers-on-elements,-document-objects,-and-window-objects)

### Footnotes

This section contains a longer explanations for changes when needed.

- I removed 'autofocus' from Button, Input, Keyget, Select, and Textarea. They have gotten it back via extending HTML\element. This attribute should be available to all HTML elements. According to the HTML spec: _The following attributes are common to and may be specified on all HTML elements_, see `3.2.6 Global attributes`.
- The 'is' attribute should be a name of a defined Custom Element. This /could/ be classname\<\_>, however, this is too restricive. Non-XHP js code may define these on the fly. Therefore, the 'string' typehint was used.

### Breaking changes that could be made to XHP

`HTML\\element::dir` has type `string`, this should really be `enum {'ltr', 'rtl', 'auto'}`, see `3.2.6.4 The dir attribute`
