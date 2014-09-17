/* Functionality of the RSVP display widget. */
(function ($) {  
  Drupal.behaviors.showRSVPs = {
    attach: function (context, settings) {
      
      $('#impetus-panes-show-rsvps-custom-pane-edit-form select#edit-event', context).once('showRSVPs', function () {
        $(this).chosen({'width': '250px'});
      });
      
    }
  };
})(jQuery);