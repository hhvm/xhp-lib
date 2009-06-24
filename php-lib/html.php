<?php

/**
 * This is the base library of HTML elements for use in XHP. This includes all
 * non-deprecated tags and attributes. Elements in this file should stay as
 * close to spec as possible. Facebook-specific extensions should go into their
 * own elements.
 */
class XHPHTMLElement extends XHPPrimitive implements JavascriptExpression {
  protected
    $tagName;

  public function js() {
    return jsprint('$(%s)', $this->requireUniqueId());
  }

  protected function requireUniqueId() {
    // TODO: Implement something on AsyncRequest that returns the number of
    //       requests sent so far so we can remove the microtime(true) thing.
    static $uniqueId = 0;
    if (empty($this->attributes['id'])) {
      $this->attributes['id'] = 'u' . (microtime(true) * 100) . '_' . (++$uniqueId);
    }
    return $this->attributes['id'];
  }

  protected final function renderBaseAttrs() {
    $buf = '<'.$this->tagName;
    if ($this->attributes) {
      foreach ($this->attributes as $key => $val) {
        if ($val !== null) {
          $buf .= ' ' . txt2html($key) . '="' . txt2html($val) . '"';
        }
      }
    }
    return $buf;
  }

  protected function render() {
    // TODO: Is this needed? I don't think so...
    return $this;
  }

  protected function supportedAttributes() {
    return array_merge(array(
      'accesskey', 'class', 'dir', 'id', 'lang', 'style', 'tabindex', 'title',
      'onabort', 'onblur', 'onchange', 'onclick', 'ondblclick', 'onerror',
      'onfocus', 'onkeydown', 'onkeypress', 'onkeyup', 'onload', 'onmousedown',
      'onmousemove', 'onmouseout', 'onmouseover', 'onmouseup', 'onreset',
      'onresize', 'onselect', 'onsubmit', 'onunload',
    ), parent::supportedAttributes());
  }

  public function __toString() {
    $buf = $this->renderBaseAttrs() . '>';
    foreach ($this->children as $child) {
      if ($child instanceof XHPPrimitive) {
        $buf .= $child->render();
      } else if ($child instanceof HTML) {
        $buf .= $child->__do_not_access_me_or_you_will_be_fired;
      } else {
        // TODO: Hack, we can get constructed with an array() as a child?
        // marcel -> epriestley: what is this?
        if (!empty($child) || !is_array($child)) {
          $buf .= txt2html($child);
        }
      }
    }
    $buf .= '</'.$this->tagName.'>';
    return $buf;
  }
}

/**
 * Subclasses of XHPHTMLSingleton may not contain children. When rendered they
 * will be in singleton (<img />, <br />) form.
 */
class XHPHTMLSingleton extends XHPHTMLElement {
  public function __toString() {
    if ($this->children) {
      throw new Exception(
        'Sub-class of XHPHTMLSingleton ['.get_class($this).'] may not have '.
        'children.'
      );
    }
    return $this->renderBaseAttrs() . ' />';
  }
}

/**
 * Subclasses of XHPHTMLPseudoSingleton may contain exactly zero or one
 * children. When rendered they will be in full open\close form, no matter how
 * many children there are.
 */
class XHPHTMLPseudoSingleton extends XHPHTMLElement {
  protected function escape($txt) {
    return txt2html($txt);
  }

  public function __toString() {
    $buf = $this->renderBaseAttrs();
    if ($this->children) {
      $child = $this->children[0];
      if (isset($this->children[1])) {
        throw new Exception(
          'Sub-class of XHPHTMLPseudoSingleton ['.get_class($this).'] must '.
          'have exactly 0 or 1 children.'
        );
      }
      $buf .= '>' . $this->escape($child);
    } else {
      $buf .= '>';
    }
    return $buf . '</'.$this->tagName.'>';
  }
}

element a extends XHPHTMLElement {
  protected
    $tagName = 'a';

  protected function supportedAttributes() {
    return array_merge(array(
      'href', 'name', 'rel', 'target',
    ), parent::supportedAttributes());
  }
}

element abbr extends XHPHTMLElement {
  protected
    $tagName = 'abbr';
}

element acronym extends XHPHTMLElement {
  protected
    $tagName = 'acronym';
}

element address extends XHPHTMLElement {
  protected
    $tagName = 'address';
}

element area extends XHPHTMLElement {
  protected
    $tagName = 'area';

  protected function supportedAttributes() {
    return array_merge(array(
      'alt', 'coords', 'href', 'nohref', 'target',
    ), parent::supportedAttributes());
  }
}

element b extends XHPHTMLElement {
  protected
    $tagName = 'b';
}

element base extends XHPHTMLSingleton {
  protected
    $tagName = 'base';

  protected function supportedAttributes() {
    return array_merge(array(
      'href', 'target',
    ), parent::supportedAttributes());
  }
}

element big extends XHPHTMLElement {
  protected
    $tagName = 'big';
}

element blockquote extends XHPHTMLElement {
  protected
    $tagName = 'blockquote';

  protected function supportedAttributes() {
    return array_merge(array(
      'cite',
    ), parent::supportedAttributes());
  }
}

element body extends XHPHTMLElement {
  protected
    $tagName = 'body';
}

element br extends XHPHTMLSingleton {
  protected
    $tagName = 'br';
}

element button extends XHPHTMLElement {
  protected
    $tagName = 'button';

  protected function supportedAttributes() {
    return array_merge(array(
      'disabled', 'name', 'type', 'value',
    ), parent::supportedAttributes());
  }
}

element caption extends XHPHTMLElement {
  protected
    $tagName = 'caption';
}

element cite extends XHPHTMLElement {
  protected
    $tagName = 'cite';
}

element code extends XHPHTMLElement {
  protected
    $tagName = 'code';
}

element col extends XHPHTMLElement {
  protected
    $tagName = 'col';

  protected function supportedAttributes() {
    return array_merge(array(
      'align', 'char', 'charoff', 'span', 'valign', 'width',
    ), parent::supportedAttributes());
  }
}

element colgroup extends XHPHTMLElement {
  protected
    $tagName = 'colgroup';

  protected function supportedAttributes() {
    return array_merge(array(
      'align', 'char', 'charoff', 'span', 'valign', 'width',
    ), parent::supportedAttributes());
  }
}

element dd extends XHPHTMLElement {
  protected
    $tagName = 'dd';
}

element del extends XHPHTMLElement {
  protected
    $tagName = 'del';

  protected function supportedAttributes() {
    return array_merge(array(
      'cite', 'datetime',
    ), parent::supportedAttributes());
  }
}

element div extends XHPHTMLElement {
  protected
    $tagName = 'div';
}

element dfn extends XHPHTMLElement {
  protected
    $tagName = 'dfn';
}

element dl extends XHPHTMLElement {
  protected
    $tagName = 'dl';
}

element dt extends XHPHTMLElement {
  protected
    $tagName = 'dt';
}

element em extends XHPHTMLElement {
  protected
    $tagName = 'em';
}

element fieldset extends XHPHTMLElement {
  protected
    $tagName = 'fieldset';
}

element form extends XHPHTMLElement {
  protected
    $tagName = 'form';

  protected function supportedAttributes() {
    return array_merge(array(
      'action', 'accept', 'accept-charset', 'enctype', 'method', 'name',
      'target',
    ), parent::supportedAttributes());
  }
}

element frame extends XHPHTMLElement {
  protected
    $tagName = 'frame';

  protected function supportedAttributes() {
    return array_merge(array(
      'frameborder', 'longdesc', 'marginheight', 'marginwidth', 'name',
      'noresize', 'scrolling', 'src',
    ), parent::supportedAttributes());
  }
}

element frameset extends XHPHTMLElement {
  protected
    $tagName = 'frameset';
}

element h1 extends XHPHTMLElement {
  protected
    $tagName = 'h1';
}

element h2 extends XHPHTMLElement {
  protected
    $tagName = 'h2';
}

element h3 extends XHPHTMLElement {
  protected
    $tagName = 'h3';
}

element h4 extends XHPHTMLElement {
  protected
    $tagName = 'h4';
}

element h5 extends XHPHTMLElement {
  protected
    $tagName = 'h5';
}

element h6 extends XHPHTMLElement {
  protected
    $tagName = 'h6';
}

element head extends XHPHTMLElement {
  protected
    $tagName = 'head';

  protected function supportedAttributes() {
    return array_merge(array(
      'profile',
    ), parent::supportedAttributes());
  }
}

element hr extends XHPHTMLSingleton {
  protected
    $tagName = 'hr';
}

element html extends XHPHTMLElement {
  protected
    $tagName = 'html';

  protected function supportedAttributes() {
    return array_merge(array(
      'xmlns',
    ), parent::supportedAttributes());
  }
}

element i extends XHPHTMLElement {
  protected
    $tagName = 'i';
}

element iframe extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'iframe';

  protected function supportedAttributes() {
    return array_merge(array(
      'frameborder', 'height', 'longdesc', 'marginheight', 'marginwidth',
      'name', 'scrolling', 'src', 'width',
    ), parent::supportedAttributes());
  }
}

element img extends XHPHTMLSingleton {
  protected
    $tagName = 'img';

  protected function supportedAttributes() {
    return array_merge(array(
      'alt', 'src', 'width', 'height',
    ), parent::supportedAttributes());
  }
}

element input extends XHPHTMLSingleton {
  protected
    $tagName = 'input';

  protected function supportedAttributes() {
    return array_merge(array(
      'accept', 'align', 'alt', 'checked', 'disabled', 'maxlength', 'name',
      'readonly', 'size', 'src', 'type', 'value',
    ), parent::supportedAttributes());
  }
}

element ins extends XHPHTMLElement {
  protected
    $tagName = 'ins';

  protected function supportedAttributes() {
    return array_merge(array(
      'cite', 'datetime',
    ), parent::supportedAttributes());
  }
}

element kbd extends XHPHTMLElement {
  protected
    $tagName = 'kbd';
}

element label extends XHPHTMLElement {
  protected
    $tagName = 'label';

  protected function init() {
    parent::init();
    if ($for = $this->getAttribute('for', false)) {
      if ($for instanceof XHPHTMLElement) {
        $this->setAttribute('for', $for->requireUniqueId());
      }
    }
  }

  public function setAttribute($attr, $val) {
    if ($attr == 'for' && $val instanceof XHPHTMLElement) {
      parent::setAttribute('for', $val->requireUniqueId());
    } else {
      parent::setAttribute($attr, $val);
    }
  }

  protected function supportedAttributes() {
    return array_merge(array(
      'for',
    ), parent::supportedAttributes());
  }
}

element legend extends XHPHTMLElement {
  protected
    $tagName = 'legend';
}

element li extends XHPHTMLElement {
  protected
    $tagName = 'li';
}

element link extends XHPHTMLSingleton {
  protected
    $tagName = 'link';

  protected function supportedAttributes() {
    return array_merge(array(
      'charset', 'href', 'hreflang', 'media', 'rel', 'rev', 'target', 'type',
    ), parent::supportedAttributes());
  }
}

element map extends XHPHTMLSingleton {
  protected
    $tagName = 'map';

  protected function supportedAttributes() {
    return array_merge(array(
      'name',
    ), parent::supportedAttributes());
  }
}

element meta extends XHPHTMLSingleton {
  protected
    $tagName = 'meta';

  protected function supportedAttributes() {
    return array_merge(array(
      'content', 'http-equiv', 'name', 'scheme',
    ), parent::supportedAttributes());
  }
}

element noframes extends XHPHTMLElement {
  protected
    $tagName = 'noframes';
}

element noscript extends XHPHTMLElement {
  protected
    $tagName = 'noscript';
}

element object extends XHPHTMLSingleton {
  protected
    $tagName = 'object';

  protected function supportedAttributes() {
    return array_merge(array(
      'align', 'archive', 'border', 'classid', 'codebase', 'codetype', 'data',
      'declare', 'height', 'hspace', 'name', 'standby', 'type', 'usemap',
      'vspace', 'width',
    ), parent::supportedAttributes());
  }
}

element ol extends XHPHTMLElement {
  protected
    $tagName = 'ol';
}

element optgroup extends XHPHTMLSingleton {
  protected
    $tagName = 'optgroup';

  protected function supportedAttributes() {
    return array_merge(array(
      'label', 'disabled',
    ), parent::supportedAttributes());
  }
}

element option extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'option';

  protected function supportedAttributes() {
    return array_merge(array(
      'disabled', 'label', 'selected', 'value',
    ), parent::supportedAttributes());
  }
}

element p extends XHPHTMLElement {
  protected
    $tagName = 'p';
}

element param extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'param';

  protected function supportedAttributes() {
    return array_merge(array(
      'name', 'type', 'value', 'valuetype',
    ), parent::supportedAttributes());
  }
}

element pre extends XHPHTMLElement {
  protected
    $tagName = 'pre';
}

element q extends XHPHTMLElement {
  protected
    $tagName = 'q';

  protected function supportedAttributes() {
    return array_merge(array(
      'cite',
    ), parent::supportedAttributes());
  }
}

// deprecated
element s extends XHPHTMLElement {
  protected
    $tagName = 's';
}

element samp extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'samp';
}

element script extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'script';

  protected function supportedAttributes() {
    return array_merge(array(
      'charset', 'defer', 'src', 'type',
    ), parent::supportedAttributes());
  }
}

element select extends XHPHTMLElement {
  protected
    $tagName = 'select';

  protected function supportedAttributes() {
    return array_merge(array(
      'disabled', 'multiple', 'name', 'size',
    ), parent::supportedAttributes());
  }
}

element small extends XHPHTMLElement {
  protected
    $tagName = 'small';
}

element span extends XHPHTMLElement {
  protected
    $tagName = 'span';
}

element strong extends XHPHTMLElement {
  protected
    $tagName = 'strong';
}

element style extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'style';

  protected function supportedAttributes() {
    return array_merge(array(
      'media', 'type',
    ), parent::supportedAttributes());
  }
}

element sub extends XHPHTMLElement {
  protected
    $tagName = 'sub';
}

element sup extends XHPHTMLElement {
  protected
    $tagName = 'sup';
}

element table extends XHPHTMLElement {
  protected
    $tagName = 'table';

  protected function supportedAttributes() {
    return array_merge(array(
      'border', 'cellpadding', 'cellspacing', 'frame', 'rules', 'summary',
      'width',
    ), parent::supportedAttributes());
  }
}

element tbody extends XHPHTMLElement {
  protected
    $tagName = 'tbody';

  protected function supportedAttributes() {
    return array_merge(array(
      'align', 'char', 'charoff', 'valign',
    ), parent::supportedAttributes());
  }
}


element td extends XHPHTMLElement {
  protected
    $tagName = 'td';

  protected function supportedAttributes() {
    return array_merge(array(
      'abbr', 'align', 'axis', 'char', 'charoff', 'colspan', 'headers',
      'rowspan', 'scope', 'valign',
    ), parent::supportedAttributes());
  }
}

element textarea extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'textarea';

  protected function supportedAttributes() {
    return array_merge(array(
      'cols', 'rows', 'disabled', 'name', 'readonly',
    ), parent::supportedAttributes());
  }
}

element tfoot extends XHPHTMLElement {
  protected
    $tagName = 'tfoot';

  protected function supportedAttributes() {
    return array_merge(array(
      'align', 'char', 'charoff', 'valign',
    ), parent::supportedAttributes());
  }
}

element th extends XHPHTMLElement {
  protected
    $tagName = 'th';

  protected function supportedAttributes() {
    return array_merge(array(
      'abbr', 'align', 'axis', 'char', 'charoff', 'colspan', 'headers',
      'rowspan', 'scope', 'valign',
    ), parent::supportedAttributes());
  }
}

element thead extends XHPHTMLElement {
  protected
    $tagName = 'thead';

  protected function supportedAttributes() {
    return array_merge(array(
      'align', 'char', 'charoff', 'valign',
    ), parent::supportedAttributes());
  }
}

element title extends XHPHTMLPseudoSingleton {
  protected
    $tagName = 'title';
}

element tr extends XHPHTMLElement {
  protected
    $tagName = 'tr';

  protected function supportedAttributes() {
    return array_merge(array(
      'align', 'char', 'charoff', 'valign',
    ), parent::supportedAttributes());
  }
}

element tt extends XHPHTMLElement {
  protected
    $tagName = 'tt';
}

// deprecated
element u extends XHPHTMLElement {
  protected
    $tagName = 'u';
}

element ul extends XHPHTMLElement {
  protected
    $tagName = 'ul';
}

element var extends XHPHTMLElement {
  protected
    $tagName = 'var';
}
