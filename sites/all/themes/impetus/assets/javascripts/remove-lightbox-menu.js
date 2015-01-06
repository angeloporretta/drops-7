jQuery( document ).ready(function() {
    
    var iframe = jQuery("iframe");
    if (iframe.length > 0) {
      var iframe_body = jQuery("#oa-navbar");
      iframe_body.css("display" , "none");
      var body = jQuery("body");
      body.css("margin-top" , 0);
      body.css("padding-top" , 0);
      var main = jQuery("#main-wrapper");
      main.css("margin-top" , 0);
  	}

});