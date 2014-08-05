(function ($) {
  $(document).ready(function() {
    // Handle toolbar collapse.
    $('.oa-navigation .btn-navbar-menu').click(function(e) {
      e.preventDefault();
      var navMenuCollapse = $('.oa-navigation .nav-menu-collapse');
      var height = (navMenuCollapse.height() == 0) ? 'auto' : 0;
      navMenuCollapse.height(height);
    });

    // adjust the position of the IPE buttons
    var $ipe = $('#panels-ipe-control-container');
    if ($ipe.length) {
      var $main = $('#main');
      var $element = $ipe.detach();
      $main.prepend($element);
    }
    
    // Handle auto-expansion of oa group menu.
    $('.pane-og-menu-single-menu ul li').removeClass('expanded').addClass('collapsed');
    $('.pane-og-menu-single-menu ul li').find('ul').css('display', 'none');
    
    var nestedFormItem = $('.pane-og-menu-single-menu ul li ul').find('a.active');
    if (nestedFormItem.length > 0) {
      var menuToggleButtons = $(nestedFormItem).parents('ul.menu').siblings('a').children('.dhtml-menu-icon');
      $(menuToggleButtons).each(function(){
        if ($(this).parent('a').parent('li').hasClass('collapsed')) {
          $(this).click();
        }
      });
    }
  });
})(jQuery);
