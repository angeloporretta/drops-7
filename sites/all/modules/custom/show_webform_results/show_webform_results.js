(function ($) {  
  Drupal.behaviors.showWebformResults = {
    attach: function (context, settings) {
      
      $('.webform-client-form', context).once('showWebformResults', function () {

        if ($(this).find('.webform-public-results').length > 0) {
          
          var resultsHtml = $(this).find('.webform-public-results').get(0);
          $(resultsHtml).remove();
          $(this).find('.webform-submit').after(resultsHtml);
        }
        
      });
    }
  };
})(jQuery);