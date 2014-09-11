/**
 * @file: Simply adds the chosen jquery plugin to the menu parent selector on node edit page.
 */
(function ($) {
  $(document).ready(function() {
    $('.form-item-menu-parent select').chosen({'width': '85%'});
  });
})(jQuery);
