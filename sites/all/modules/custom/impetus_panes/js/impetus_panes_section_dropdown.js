/* Functionality of the section dropdown pane */
(function ($) {  
  Drupal.behaviors.dropdownSections = {
    attach: function (context, settings) {
      
      if ($('body.mobile').length === 0) {
      $('#mini-panel-oa_toolbar_panel .spaces-section-dropdown > li > a').hover(function(){
        
        $('#mini-panel-oa_toolbar_panel .spaces-section-dropdown .nested').addClass('hide').removeClass('show');
        var nestedMenu = $(this).siblings('ul.nested');
        $(nestedMenu).removeClass('hide').addClass('show');
      },
      function(){
        var nestedMenu = $(this).siblings('ul.nested');
        var hideTimeout = setTimeout(function(){
          $(nestedMenu).addClass('hide').removeClass('show');
        }, 1000);
        
        $(nestedMenu).hover(
          function(){
            clearTimeout(hideTimeout);
          },
          function(){
            setTimeout(function(){
              $(nestedMenu).addClass('hide').removeClass('show');
            }, 500);
          }
        );
      });
    } 
    }
  };
})(jQuery);