jQuery( document ).ready(function() {

     jQuery("a").click(function() {
     jQuery("#lightboxFrame").on("load" , function(){
    var iframe_body = jQuery("#lightboxFrame").contents().find("#oa-navbar");
     if (iframe_body.length > 0) {
      iframe_body.css("display" , "none");
      var body = jQuery("#lightboxFrame").contents().find("body");
      body.attr('style' , "margin-top: 0px !important");
      body.css("padding-top" , 0);
      var main = jQuery("#lightboxFrame").contents().find("#main-wrapper");
      main.css("margin-top" , 0);
     }
  });
     });
});