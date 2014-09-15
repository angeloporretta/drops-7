<?php
/**
 * @file: Form render functions and other functions only for admins and settings pages.
 */

/**
 * Helper function.
 * Renders the file preview settings form.
 */
function file_preview_get_settings_form() {
  
  $form = array();
  
  $form['file_preview_groupdocs_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Groupdocs Username/Email'),
    '#required' => TRUE,
    '#default_value' => variable_get('file_preview_groupdocs_username', ''),
  );
    
  $form['file_preview_groupdocs_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Groupdocs Password'),
    '#maxlength' => 64,
    '#required' => TRUE,
    '#default_value' => variable_get('file_preview_groupdocs_password', ''),
  );
  
  $form['file_preview_groupdocs_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Groupdocs Client ID'),
    '#required' => TRUE,
    '#default_value' => variable_get('file_preview_groupdocs_client_id', ''),
  );
  
  $form['file_preview_groupdocs_private_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Groupdocs Private Key'),
    '#required' => TRUE,
    '#default_value' => variable_get('file_preview_groupdocs_private_key', ''),
  );
  
  $form = system_settings_form($form);
  
  return $form;
}