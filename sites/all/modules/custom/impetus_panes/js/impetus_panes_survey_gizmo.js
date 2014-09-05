/* Functionality of the survey gizmo embed pane */
(function ($) {  
  Drupal.behaviors.surveyGizmo = {
    attach: function (context, settings) {
      var firstName = Drupal.settings.impetusPanes.firstName;
      var lastName = Drupal.settings.impetusPanes.lastName;
      var email = Drupal.settings.impetusPanes.email;
      
      setTimeout(function(){
        
        $('.sg-question-title').each(function(index, element){
          var label = $(element).find('label').text();
          
          if (label.match(/First Name/i)) {
            $(element).siblings('.sg-question-options').find('input[type="text"]').val(firstName);
          }
          else if (label.match(/Last Name/i)) {
            $(element).siblings('.sg-question-options').find('input[type="text"]').val(lastName);
          }
          else if (label.match(/Your Name/i)) {
            $(element).siblings('.sg-question-options').find('input[type="text"]').val(firstName + ' ' + lastName);
          }
          else if (label.match(/mail/i)) {
            $(element).siblings('.sg-question-options').find('input').val(email);
          }
        }); 
      }, 1250);
      
    }
  };
})(jQuery);