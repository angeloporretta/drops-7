jQuery(document).ready(function(){
  var table_width = jQuery("table.webform_report").width();
  var scroll_width = jQuery("#doubleScroll").width();
  if (scroll_width < table_width) {
    jQuery("#doubleScroll").doubleScroll({
      contentElement: jQuery("table.webform_report"),
      onlyIfScroll: true
    });
  }
});