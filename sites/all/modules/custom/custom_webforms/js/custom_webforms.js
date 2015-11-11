function switchClass(){
	if (jQuery(".form-item.form-type-textfield.form-item-extra-ranking-col").hasClass("hide-item")) {
		jQuery(".form-item.form-type-textfield.form-item-extra-ranking-col").removeClass("hide-item");
		jQuery("#edit-extra-ranking-fieldset").addClass("hide-item");
	} else {
		jQuery(".form-item.form-type-textfield.form-item-extra-ranking-col").addClass("hide-item");
		jQuery("#edit-extra-ranking-fieldset").removeClass("hide-item");
	}
}

jQuery(document).ready(function(){
	if (jQuery("#edit-extra-ranking-col").hasClass("hide-item")) {
		jQuery("#edit-extra-ranking-col").parent().addClass("hide-item");
		jQuery("#edit-extra-ranking-col").removeClass("hide-item");
	}
	jQuery("input#edit-extra-ranking-col-type").click(function(){
		switchClass();
	});
});