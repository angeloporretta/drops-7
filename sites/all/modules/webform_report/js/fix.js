jQuery(document).ready(function(){
	var width = jQuery(".webform_report.table").width();
	// jQuery(".dummy-wrapper").css("width", width);
	jQuery(".dummy-content").css("width", width);
	console.log(width);
  jQuery(".dummy-wrapper").scroll(function(){
    jQuery("#block-system-main .content").scrollLeft(jQuery(".dummy-wrapper").scrollLeft());
  });
  jQuery("#block-system-main .content").scroll(function(){
    jQuery(".dummy-wrapper").scrollLeft(jQuery("#block-system-main .content").scrollLeft());
  });
});