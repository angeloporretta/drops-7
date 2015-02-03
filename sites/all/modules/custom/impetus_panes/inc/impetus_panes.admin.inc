<?php
/**
 * @file: Administrative forms and resources.
 */

/**
 * Form render function.
 * Renders the module's settings form.
 */
function impetus_panes_settings_form() {
  $form = array();
  
  $form['survey_gizmo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Survey Gizmo'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  
  $form['survey_gizmo']['impetus_panes_sg_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Survey Gizmo Email'),
    '#default_value' => variable_get('impetus_panes_sg_email', ''),
    '#required' => TRUE,
  );
  
  $form['survey_gizmo']['impetus_panes_sg_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Survey Gizmo Password'),
    '#default_value' => variable_get('impetus_panes_sg_password', ''),
    '#required' => TRUE,
  );
  
  $form = system_settings_form($form);
  return $form;
}