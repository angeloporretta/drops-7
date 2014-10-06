(function ($) {
  $(document).ready(function() {
    
    // Adding a body class if the site goes mobile.
    if ($(window).width() < 980) {
      $('body').addClass('mobile');
    }
    
    $(window).resize(function() {
      if ($(window).width() < 980) {
        $('body').addClass('mobile');
      }
      else {
        $('body').removeClass('mobile');
      }
    });
    
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
       
        if ($(nestedFormItem).parent('li.dhtml-menu').hasClass('collapsed')) {
          $(nestedFormItem).children('a.dhtml-menu-icon').click();
        }
        
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
    
    // Handle space menu in top bar.
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
    
    // Changes to file node edit forms.
    $('body.page-node #contextual-tabs .dropdown-menu a').each(function(index, element){
      if ($(element).attr('href').indexOf('revisions') > -1) {
        var revisionItem = $(element).parent();
        $(revisionItem).remove();
        $(revisionItem).children('a').addClass('btn btn-small').text(Drupal.t('Versions'));
        $('#contextual-tabs').append(revisionItem);
      }
    });
    
    if ($('#file-node-form #edit-field-uploaded-file .file-widget input[type="submit"]').attr('value') == 'Remove') {
      $('#file-node-form #edit-field-uploaded-file .file-widget input[type="submit"]').attr('value', Drupal.t('Upload New Version'));
    }
    
    // Changes to taxonomy pages.
    if ($('.file-breadcrumb').length > 0) {
      var breadcrumbHtml = $('.file-breadcrumb');
      $('.file-breadcrumb').remove();
      $('#main #content .inner').before($(breadcrumbHtml));
    }
    
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
    
    // Video upload fields.
    $('.field-type-video input[type="file"]').live('change', function(){
      $(this).next('input[type="submit"]').mousedown();
      $('#main-wrapper').append('<div class="video-overlay"></div>');
      $('.video-overlay').css({
        'position': 'absolute',
        'z-index': '1000',
        'left': '0',
        'top': '0',
        'background': '#fff',
        'height': $(document).height() + 'px',
        'width': $(document).width() + 'px',
        'opacity': '0.85',
        'filter': 'alpha(opacity=85)',
        'font-size': '16px',
      }).after('<div class="video-download-prompt"><p>' + Drupal.t('Please wait while your video gets uploaded...') + '<br/>' + Drupal.t('This may take a several minutes depending on your internet connection upload speed.') + '<br/><br/><img src="/sites/all/themes/impetus/assets/images/video-loading.gif" alt="" /></p></div>');
      $('.video-download-prompt').css({
        'position': 'fixed',
        'z-index': '2000',
        'top': '40%',
        'left': '0px',
        'text-align': 'center',
        'display': 'block',
        'width': '100%',
      });
      setInterval(function(){
        if ($('.ajax-progress-throbber').length == 0) {
          $('.video-overlay').remove();
          $('.video-download-prompt').remove();
        }
      }, 
      3000);
    });
    
    // Sticky headers for metrics tables.
    $('table.metrics-table').fixedHeaderTable({ 
      altClass: 'odd',
      autoShow: true
    });
    
  });
})(jQuery);
