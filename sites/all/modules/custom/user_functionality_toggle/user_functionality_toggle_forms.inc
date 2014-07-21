<?php
/**
 * @file: All code for admin forms.
 */

/**
 * Helper Function.
 * Renders the administrative form.
 */
function user_functionality_toggle_render_admin_form() {
  
  $form = array();
  
  $form['toggle_remember_me'] = array(
    '#title' => t('Turn on "Remember Me" functionality.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('toggle_remember_me', 1),
  );
  
  $form['toggle_forgot_password'] = array(
    '#title' => t('Turn on "Forgot Password" functionality.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('toggle_forgot_password', 1),
  );
  
  $form = system_settings_form($form);
  
  return $form;
}