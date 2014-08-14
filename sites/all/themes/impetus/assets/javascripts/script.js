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
    if ($('body.node-type-oa-section').length < 1) {

      var nestedFormItem = $('.pane-og-menu-single-menu ul li ul').find('a.active');
      if (nestedFormItem.length > 0) {
        var menuToggleButtons = $(nestedFormItem).parents('ul.menu').siblings('a').children('.dhtml-menu-icon');
        $(menuToggleButtons).each(function(){
          if ($(this).parent('a').parent('li').hasClass('collapsed')) {
            $(this).click();
          }
        });
      }
    }
    else {
      $('.pane-og-menu-single-menu ul a.active .dhtml-menu-icon').click();
    }
    
    // Other styling for oa group menu.
    $('.content .pane-og-menu-single-menu ul a.active').siblings('ul').find('a').css('color', '#333');
    $('.content .pane-og-menu-single-menu ul .expanded a').css('color', '#333');
    
    // Handle dashboard space dropdown menu.
    $('.content .spaces-section-dropdown > li').click(function(){
      if ($(this).children('.nested').hasClass('show')) {
        $('#panels-ipe-regionid-sidebar .spaces-section-dropdown > li').removeClass('open');
        $(this).addClass('open');
      }
    });
  });
})(jQuery);
