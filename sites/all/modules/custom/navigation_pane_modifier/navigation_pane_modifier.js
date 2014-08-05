/*
 * @file: The main functionality. Just swaps out the img source of the logo so that we can go to the dashboard.
 */
(function ($) {  
  Drupal.behaviors.navigationPane = {
    attach: function (context, settings) {
      $('.oa-menu-banner a', context).once('navigationPane', function () {
        $(this).attr('href', '/user/' + Drupal.settings.navigation_pane_modifier.uid + '/view');
      });
    }
  };
})(jQuery);