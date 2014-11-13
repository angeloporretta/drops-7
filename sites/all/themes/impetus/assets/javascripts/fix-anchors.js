jQuery( document ).ready(function() {
	//click on a element event
	jQuery("a").click(function(event){
		//get the href of the a element
		var href = jQuery(this).attr('href');
		//if first character of string is # 
		if (href.indexOf('#') == 0) {
			//prevent default functionality
			event.preventDefault();
			//get the id of the element to navigate to
			var id = href.substring(1,href.length);
			// get the element with that id
			var element = document.getElementById(id);
			//get the position of the element in page
			var position = jQuery(element).offset().top;
			//get the size of the header
			var header = jQuery('#oa-navbar').height();
			//scroll window to the location of the element
			jQuery(window).scrollTop(position-header);
		}
	});
  
});
