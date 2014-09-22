/**
 * @file: All javascript behavior to do with the menu edit.
 */
(function ($) {
  
  Drupal.behaviors.formModifierMenuEdit = {
    attach: function (context, settings) {
      $('#menu-overview-form', context).once('menuEdit', function () {
        var searchMenuField = $(this).find('.form-item-drill-down-parents');
        $(searchMenuField).remove();
        $(this).find('.form-item-description').after(searchMenuField);
        drillDownMenuItems($('.form-item-drill-down-parents select').val());
        $('.form-item-drill-down-parents select').change(function(e){
          drillDownMenuItems($(this).val());
        });
        
        /**
         * Helper Function.
         * Hides and displays table menu items on the HUGE menu order shifting list.
         * @param {string} parentItemName: The name of the highest level (level 0) menu item.
         * @returns {nothing}
         */
        function drillDownMenuItems(parentItemName) {
          if (parentItemName != '') {
            $('#menu-overview tr').css('display', 'none');
            var highLevelTableItem = $('#menu-overview tr[title="' + parentItemName + '"]');
            $(highLevelTableItem).css('display', 'table-row');
            
            var parentHasChildren = $(highLevelTableItem).next().find('.indentation').length;
            
            if (parentHasChildren > 0) {
              $(highLevelTableItem).next().css('display', 'table-row');
              var tableItem = highLevelTableItem;
              
              do {
                $(tableItem).css('display', 'table-row');
                tableItem = tableItem.next();
              }
              while ($(tableItem).find('.indentation').length > 0); 
            }
          }
          else {
            $('#menu-overview tr').css('display', 'table-row');
          }
        }
      });
    }
  };
})(jQuery);