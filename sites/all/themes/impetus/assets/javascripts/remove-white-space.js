jQuery( document ).ready(function() {
  setTimeout(function(){
    var navbar = jQuery(".navbar-fixed-top").outerHeight(true);
    jQuery("body").css("margin-top" , navbar+30);
    jQuery("body").css("padding-top" , 0);
  } , 1000);
  var title = document.getElementById("page-title");
  if (title != null) {
  	var sidebar = jQuery(".burr-flipped-sidebar");
  	sidebar.css("margin-top" , -40);
  }
});