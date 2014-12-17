jQuery( document ).ready(function() {
	if (jQuery("#oa-navbar").height() > 100) {
		var dif = jQuery("#oa-navbar").height() - 100 + 30;
		jQuery("#main-wrapper").css("margin-top" , dif);
	}

});