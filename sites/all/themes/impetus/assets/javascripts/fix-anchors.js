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
	jQuery("a").click(function(event){
	setTimeout(function(){
	var width = jQuery("#outerImageContainer").width();
	if (width > 1000) {
		jQuery("#lightbox").css("-webkit-transform" , "scale(0.6)").css("transform" , "scale(0.6)").css("-ms-transform" , "scale(0.6)");
		var container_width = jQuery("#frameContainer").width();
		var img = jQuery("iframe#lightboxFrame").contents().find("img");
		
		if (img.length == 0) {
		  if(jQuery("iframe#lightboxFrame").width() > 1000) {
			jQuery("iframe#lightboxFrame").css("width" , 1000);
		  }
		} else {
			jQuery(img).css("width" , container_width);
		}
	} else {
		var container_width = jQuery("#frameContainer").width();
		var img = jQuery("iframe#lightboxFrame").contents().find("img");
		if (img.length == 0) {
		  if(jQuery("iframe#lightboxFrame").width() > 1000) {
			jQuery("iframe#lightboxFrame").css("width" , 600);
		  }
		} else {
		  jQuery(img).css("width" , container_width);
		}
	}
	}, 1000);
});
  
});
