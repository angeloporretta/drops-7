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
    $('.content .pane-og-menu-single-menu ul a.active').siblings('ul').find('a').css('color', '#0071B3');
    $('.content .pane-og-menu-single-menu ul .expanded a').css('color', '#0071B3');
    
    // Handle dashboard space dropdown menu.
    $('.content .spaces-section-dropdown > li').click(function(){
      if ($(this).children('.nested').hasClass('show')) {
        $('#panels-ipe-regionid-sidebar .spaces-section-dropdown > li').removeClass('open');
        $(this).addClass('open');
      }
    });
    
    // Coloring for calendars.
    addCalendarColors();
    $('.fc-button').live('click', function(){
      addCalendarColors();
    });
    
    /**
     * Helper function.
     * Adds color coding to fc calendars. This is based on the field_color_code field.
     */
    function addCalendarColors() {
      $('.fullcalendar-content .fullcalendar-event-details').each(function(index, element){
        var hexColor = $(element).attr('color-style');
        var calendarElement = $('.fullcalendar .fc-event[href="' + $(element).attr('href') + '"]');
        $(calendarElement).css({
          'background-color': hexColor,
          'border-color': hexColor
        });
        $(calendarElement).find('.fc-event-time').css({
          'background-color': hexColor,
          'border-color': hexColor
        });
      });
    }
    
    // Changes to file node pages.
    $('.node-file .field-name-field-uploaded-file span.file a').attr('download', '');
    $('.files-in-this-folder-list .file a').attr('download', '');

    $('.files-in-this-folder-list .file a').each(function(index, element){
      if ($(element).text().length > 22) {
        $(element).text($(element).text().substring(0, 22) + '...');
      }
    });
    
    // Changes to node edit forms.
    if ($('.regular-user .node-form .pane-node-form-menu').has('h3').get(0) == undefined) {
      $('.regular-user .node-form .pane-node-form-menu').css('display', 'none');
    }
    if ($('.regular-user .node-form .pane-node-form-publishing').has('h3').get(0) == undefined) {
      $('.regular-user .node-form .pane-node-form-publishing').css('display', 'none');
    }
    if ($('.regular-user .node-form .pane-node-form-author').has('h3').get(0) == undefined) {
      $('.regular-user .node-form .pane-node-form-author').css('display', 'none');
    }
    
  });
})(jQuery);
