(function ($) {
  Drupal.behaviors.formModifier = {
    attach: function (context, settings) {
      $('.node-form #edit-oa-parent-space-und', context).once('changeLabels', function () {
        $(this).find('.fieldset-legend').text(Drupal.t('Groups'));
        $(this).find('label').text(Drupal.t('Groups That Have Access'));
        $(this).find('.description').text('');
      });
    }
  };
})(jQuery);