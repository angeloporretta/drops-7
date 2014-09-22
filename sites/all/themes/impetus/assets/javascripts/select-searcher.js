/**
 * @file: Simply adds the chosen jquery plugin to a bunch of select elements.
 */
(function ($) {
  $(document).ready(function() {
    
    if ($('form.node-form').length > 0) {
      $('.form-item-menu-parent select').chosen({'width': '85%'});
      setInterval(function(){
        var selectWrapper = $('.node-form #reference-options-limit-oa-section-ref');
        if ($(selectWrapper).find('#edit_oa_section_ref_und_chosen').length < 1) {
          $(selectWrapper).find('select').chosen({'width': '250px'});
        }
      }, 1000);
    }
    
    if ($('form#bulk-file-upload-add-files-form').length > 0) {
      $('form#bulk-file-upload-add-files-form .form-item-section select').chosen({'width': '250px'});
      
      setInterval(function(){
        var selectWrapper = $('form#bulk-file-upload-add-files-form .form-item-section');
        if ($(selectWrapper).find('#edit_section_chosen').length < 1) {
          $(selectWrapper).find('select').chosen({'width': '250px'});
        }
      }, 1000);
      
    }
    
    if ($('div.view-admin-views-user').length > 0) {
      $('div.view-admin-views-user form #edit-og-user-node-target-id').chosen({'width': '250px'});
    }
    
    if ($('#menu-overview-form').length > 0) {
      $('.form-item-drill-down-parents select').chosen({'width': '250px'});
    }
    
  });
})(jQuery);
