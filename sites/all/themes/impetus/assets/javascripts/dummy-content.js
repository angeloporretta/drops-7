jQuery( document ).ready(function() {
  jQuery(".dummy-link").click(function(){
  	var dummy_element = jQuery(this);
  	var click_element = dummy_element[0].children[0];
  	jQuery(click_element).click();
  });

});