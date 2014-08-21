/* Functionality of the bulk file upload page. */
(function ($) {  
  Drupal.behaviors.bulkFileUploadPage = {
    attach: function (context, settings) {
      
      $('#bulk-file-upload-add-files-form #edit-add-more', context).once('dropdownSections', function () {
        $(this).click(function(e){
          e.preventDefault();
          displayAnotherFile();
        });
      });
      
      $('#bulk-file-upload-add-files-form').delegate('input.form-file', 'change', function() {  
        $(this).next('input[type="submit"]').mousedown();
      }); 
      
      /**
       * Displays another hidden file field that was hidden through css.
       */
      function displayAnotherFile() {
        for(var i = 0; i < $('#bulk-file-upload-add-files-form .form-type-managed-file').length; i++) {
          
          if ($($('#bulk-file-upload-add-files-form .form-type-managed-file').get(i)).css('display') == 'none') {
            $($('#bulk-file-upload-add-files-form .form-type-managed-file').get(i)).css('display', 'block');
            i = $('#bulk-file-upload-add-files-form .form-type-managed-file').length;
          }
        }
      }
    }
  };
})(jQuery);