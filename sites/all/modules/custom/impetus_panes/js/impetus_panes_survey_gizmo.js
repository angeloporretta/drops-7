/* Functionality of the survey gizmo embed pane */
(function ($) {  
  Drupal.behaviors.surveyGizmo = {
    attach: function (context, settings) {
      var firstName = Drupal.settings.impetusPanes.firstName;
      var lastName = Drupal.settings.impetusPanes.lastName;
      var email = Drupal.settings.impetusPanes.email;
      var isHidden = Drupal.settings.impetusPanes.prefillsHidden;
      
      setTimeout(function(){
        
        $('.sg-question-title').each(function(index, element){
          var label = $(element).find('label').text();
          var fieldDisplay = 'block';
          
          if (isHidden) {
            fieldDisplay = 'none';
          }
          
          if (label.match(/Your First Name/i)) {
            $(element).siblings('.sg-question-options').find('input[type="text"]').val(firstName);
            $(element).parents('.sg-type-textbox').css('display', fieldDisplay);
          }
          else if (label.match(/Your Last Name/i)) {
            $(element).siblings('.sg-question-options').find('input[type="text"]').val(lastName);
            $(element).parents('.sg-type-textbox').css('display', fieldDisplay);
          }
          else if (label.match(/Your Name/i)) {
            $(element).siblings('.sg-question-options').find('input[type="text"]').val(firstName + ' ' + lastName);
            $(element).parents('.sg-type-textbox').css('display', fieldDisplay);
          }
          else if (label.match(/Your Email/i)) {
            $(element).siblings('.sg-question-options').find('input').val(email);
            $(element).parents('.sg-type-textbox').css('display', fieldDisplay);
          }
        }); 
      }, 1750);
      
    }
  };
})(jQuery);