jQuery( window ).load(function() {
  //var active = jQuery('ul.menu a.active');
  var count = 0;
  jQuery("ul.menu li.dhtml-menu a.active").each(function() {
  	var test = jQuery(this);
  	var parent = jQuery(this).parent().parent().parent();
  	var item = jQuery(parent[0]).children();
  	if (test[0].childNodes.length > 0) {
  	if (parent.hasClass("collapsed")) {
  	  var icon = jQuery(item[0]).children();
  	  jQuery(icon[0]).click();
  	} }
  });

});