/**
 * @file: All javascript behavior to do with forms provided by the privatemsg module.
 */
(function ($) {
  Drupal.behaviors.formModifierPrivateMsg = {
    attach: function (context, settings) {
      $('#privatemsg-new', context).once('privateMsgCreate', function () {
        
        var requiredTextElements = $(this).find('.form-required').parents('.form-item').find('input[type="text"]');
        var requiredTextareaElements = $(this).find('.form-required').parents('.form-item').find('textarea');

        $(this).submit(function(e){
          
          $('.form-modifier-error').remove();
          $(requiredTextElements).removeClass('error');
          $(requiredTextareaElements).removeClass('error');
          var errorMessage = '<div style="color:#B94A48;" class="form-modifier-error">' + Drupal.t('This field is required.') + '</div>';
          
          $(requiredTextElements).each(function(index, element){
            if ($(element).val() == '') {
              $(element).addClass('error').after(errorMessage);
              e.preventDefault();
            }
          });
          $(requiredTextareaElements).each(function(index, element){
            if ($(element).val() == '') {
              $(element).addClass('error').after(errorMessage);
              e.preventDefault();
            }
          }); 
        });
        
      });
    }
  };
})(jQuery);