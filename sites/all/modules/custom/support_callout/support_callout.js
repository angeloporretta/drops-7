/**
 * @file: Javascript functionality of this module.
 */
(function ($) {
  Drupal.behaviors.supportCallout = {
    attach: function (context, settings) {
      $('#support-callout-container', context).once('supportCallout', function () {
        
        $('#callout-trigger').click(function(e){

          if ($('#support-callout-message').hasClass('hide')) {
            $('#support-callout-container').animate(
              {'width' : '400px'}, 
              500,
              'swing',
              function() {
                $('#support-callout-message').addClass('show').removeClass('hide');
              }
            );
          }
          else {
            $('#support-callout-message').addClass('hide').removeClass('show');
            $('#support-callout-container').animate(
              {'width' : '160px'}, 
              500,
              'swing'
            );
          }
        });
        
      });
    }
  };
})(jQuery);