jQuery(document).ready(function() {
	jQuery("table.ranking-table input[type='radio']").click(function(){
		var button_classes = jQuery(this)[0].classList;
		for (index = 0; index < button_classes.length; index++) {
			var elements = jQuery(this).parents("table.ranking-table").find("input." + button_classes[index]);
			if (button_classes[index] != 'form-radio' && button_classes[index] != 'error') {
				for (elem_index = 0; elem_index < elements.length; elem_index++) {
					if (jQuery(elements[elem_index]).hasClass(button_classes[0]) && jQuery(elements[elem_index]).hasClass(button_classes[1])) {
						jQuery(elements[elem_index]).prop("checked", true);
					} else {
						jQuery(elements[elem_index]).prop("checked", false);
					}
				}
			}
		}
	});
});