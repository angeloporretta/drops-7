/* Functionality of the file node page. */
(function ($) {  
  Drupal.behaviors.bulkFileNodePage = {
    attach: function (context, settings) {
      
      $('#file-node-form', context).once('dropdownSections', function () {
        $(this).delegate('input.form-file', 'change', function() {  
          $(this).next('input[type="submit"]').mousedown();
        }); 
      });
      
      //$('#bulk-file-upload-add-files-form').delegate('input.form-file', 'change', function() {  
      //  $(this).next('input[type="submit"]').mousedown();
      //}); 

    }
  };
})(jQuery);