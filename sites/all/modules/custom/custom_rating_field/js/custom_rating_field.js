function switchClass(){
	if (jQuery(".form-item.form-type-textfield.form-item-extra-rating-col").hasClass("hide-item")) {
		jQuery(".form-item.form-type-textfield.form-item-extra-rating-col").removeClass("hide-item");
		jQuery("#edit-extra-rating-fieldset").addClass("hide-item");
	} else {
		jQuery(".form-item.form-type-textfield.form-item-extra-rating-col").addClass("hide-item");
		jQuery("#edit-extra-rating-fieldset").removeClass("hide-item");
	}
}

jQuery(document).ready(function(){
	if (jQuery("#edit-extra-rating-col").hasClass("hide-item")) {
		jQuery("#edit-extra-rating-col").parent().addClass("hide-item");
		jQuery("#edit-extra-rating-col").removeClass("hide-item");
	}
	jQuery("input#edit-extra-rating-col-type").click(function(){
		switchClass();
	});
});