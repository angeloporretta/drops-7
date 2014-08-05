/* Functionality of the section dropdown pane */
(function ($) {  
  Drupal.behaviors.dropdownSections = {
    attach: function (context, settings) {
      
      $('.spaces-section-dropdown .dropdown a', context).once('dropdownSections', function () {
        
        $(this).click(function(e){
          if ($(this).siblings('ul.nested').css('display') == 'none') {
            e.preventDefault();
            $('.spaces-section-dropdown .nested').addClass('hide').removeClass('show');
            $(this).siblings('ul.nested').addClass('show');
          }
        });
        
        $('#main-wrapper').click(function(){
          
          if ($('.spaces-section-dropdown .show').length > 0) {
            $('.spaces-section-dropdown .show').addClass('hide').removeClass('show');
          }
        });
        
      });
    }
  };
})(jQuery);