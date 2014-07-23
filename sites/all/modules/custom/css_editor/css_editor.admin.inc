<?php
/**
 * @file: Admin forms and functionality.
 */

/**
 * Helper function.
 * Renders the CSS Editing form.
 */
function css_editor_render_editor_form() {
  
  $form = array();
  
  $form['css_editor_css'] = array(
    '#type' => 'textarea',
    '#title' => 'CSS',
    '#description' => t('Add CSS to the box above. <strong>CSS must be properly formed or it will break the portal.</strong><br/><strong>CSS only! Any HTML or javascript will not be interpreted.</strong>'),
    '#cols' => 100,
    '#rows' => 15,
    '#default_value' => variable_get('css_editor_css', ''),
  );
  
  $form = system_settings_form($form);
  
  return $form;
}