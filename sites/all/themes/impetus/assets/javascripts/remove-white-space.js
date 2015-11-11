document.onreadystatechange = function(e)
{
      var title = jQuery("#page-title");
      if (title.length > 0) {
        var sidebar = jQuery(".burr-flipped-sidebar");
        sidebar.css("margin-top", -40);
      }
};