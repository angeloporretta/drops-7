jQuery( window ).load(function() {
  //add class active to li
  var active_item = jQuery("..panels-ipe-portlet-wrapper .pane-og-menu-single-menu .pane-content ul.menu li a.active");
  if (typeof active_item[0] != 'undefined') {
    jQuery(active_item[0]).parent().addClass('active');
  }
  var count = 0;
  jQuery("ul.menu li.dhtml-menu a.active").each(function() {
  	var test = jQuery(this);
    var parents = test.parents('.collapsed');
    var i;

    jQuery.each(parents , function(i , l){
         if (jQuery(l).hasClass("collapsed")) {
         //get childrens of li
         var children = jQuery(jQuery(l)[0]).children();
         //get childrens of a
         var get_children = jQuery(children.children(".dhtml-menu-icon"));
         //click only the items that actually have an icon next to them
         if (get_children.length > 0) {
            get_children[0].click();
         }
       }
    });
    
  });

});