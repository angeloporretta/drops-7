jQuery( document ).ready(function() {
  setTimeout(function(){
    var navbar = jQuery(".navbar-fixed-top").outerHeight(true);
      jQuery("body").css("margin-top" , navbar+30);
      jQuery("body").css("padding-top" , 0);
  } , 1000);
  var title = jQuery("#page-title");
  if (title.length > 0) {
  	var sidebar = jQuery("#panels-ipe-regionid-sidebar");
  	sidebar.css("margin-top" , -40);
  }
});