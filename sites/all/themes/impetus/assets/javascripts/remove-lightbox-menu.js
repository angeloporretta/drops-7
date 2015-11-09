(function($) {    
  if ($.fn.style) {
    return;
  }

  // Escape regex chars with \
  var escape = function(text) {
    return text.replace(/[-[\]{}()*+?.,\\^$|#\s]/g, "\\$&");
  };

  // For those who need them (< IE 9), add support for CSS functions
  var isStyleFuncSupported = !!CSSStyleDeclaration.prototype.getPropertyValue;
  if (!isStyleFuncSupported) {
    CSSStyleDeclaration.prototype.getPropertyValue = function(a) {
      return this.getAttribute(a);
    };
    CSSStyleDeclaration.prototype.setProperty = function(styleName, value, priority) {
      this.setAttribute(styleName, value);
      var priority = typeof priority != 'undefined' ? priority : '';
      if (priority != '') {
        // Add priority manually
        var rule = new RegExp(escape(styleName) + '\\s*:\\s*' + escape(value) +
            '(\\s*;)?', 'gmi');
        this.cssText =
            this.cssText.replace(rule, styleName + ': ' + value + ' !' + priority + ';');
      }
    };
    CSSStyleDeclaration.prototype.removeProperty = function(a) {
      return this.removeAttribute(a);
    };
    CSSStyleDeclaration.prototype.getPropertyPriority = function(styleName) {
      var rule = new RegExp(escape(styleName) + '\\s*:\\s*[^\\s]*\\s*!important(\\s*;)?',
          'gmi');
      return rule.test(this.cssText) ? 'important' : '';
    }
  }

  // The style function
  $.fn.style = function(styleName, value, priority) {
    // DOM node
    var node = this.get(0);
    // Ensure we have a DOM node
    if (typeof node == 'undefined') {
      return this;
    }
    // CSSStyleDeclaration
    var style = this.get(0).style;
    // Getter/Setter
    if (typeof styleName != 'undefined') {
      if (typeof value != 'undefined') {
        // Set style property
        priority = typeof priority != 'undefined' ? priority : '';
        style.setProperty(styleName, value, priority);
        return this;
      } else {
        // Get style property
        return style.getPropertyValue(styleName);
      }
    } else {
      // Get CSSStyleDeclaration
      return style;
    }
  };
})(jQuery);

jQuery( document ).ready(function() {

     jQuery("a").click(function() {
      
     jQuery("#lightboxFrame").on("load" , function(){
      var iframe_footer = jQuery("#lightboxFrame").contents().find("#footer");
     if (iframe_footer.length > 0) {
      iframe_footer.css("display" , "none");
     }
      var iframe_support = jQuery("#lightboxFrame").contents().find("#support-callout-container");
      if (iframe_support.length > 0) {
        iframe_support.css("display" , "none");
      }
    var iframe_body = jQuery("#lightboxFrame").contents().find("#oa-navbar");
     if (iframe_body.length > 0) {
      iframe_body.css("display" , "none");
      var body = jQuery("#lightboxFrame").contents().find("body");
      setTimeout(function(){
        
        body.css("margin-top" , 0);
      } , 1000);
      // body.each(function () { this.style.setProperty( 'border-top', '0px', 'important' ); });
      body.addClass("remove-margin");
      body.css("padding-top" , 0);
      var main = jQuery("#lightboxFrame").contents().find("#main-wrapper");
      main.css("margin-top" , 0);
     }

  });
     });
});