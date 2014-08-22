<?php
/**
 * @file: All functionality for forms created by this module.
 */

/**
 * Helper function.
 * Renders the add bulk files form. Will return an empty array if the user does not have permission to use the form.
 */
function bulk_file_upload_add_files_form($form, &$form_state, $tid) {
  
  $form = array();
  
  if (user_access('access bulk upload page')) {
    
    drupal_add_css(drupal_get_path('module', 'bulk_file_upload') . '/css/bulk_file_upload_upload_page.css');
    drupal_add_js(drupal_get_path('module', 'bulk_file_upload') . '/js/bulk_file_upload_upload_page.js');
    
    $form['preamble'] = array(
      '#type' => 'markup',
      '#markup' => '<h3>' . t('Upload') . '</h3>',
      '#weight' => -50,
    );

    $form['files'] = array(
      '#prefix' => '<div id="files-wrapper">',
      '#suffix' => '</div>',
      '#type' => 'fieldset',
      '#title' => t('Files you want to upload'),
    );
    
    $form['tid'] = array(
      '#type' => 'hidden',
      '#value' => $tid,
    );

    $folder = taxonomy_term_load($tid);
    $form['folder_prompt'] = array(
      '#type' => 'markup',
      '#markup' => t(
        'You will be uploading these files into the <strong>@folder_name</strong> folder.',
        array('@folder_name' => $folder->name)
      ),
      '#weight' => -49,
    );


    if (isset($_SESSION['oa_section_id'])){
      $section_node = node_load($_SESSION['oa_section_id']);

      $form['is_private'] = array(
        '#type' => 'checkbox',
        '#title' => t('These files are private.'),
        '#description' => t(
          'These files will belong to the section <strong>@section</strong> unless you uncheck this box.',
          array('@section' => $section_node->title)
        ),
        '#default_value' => 1,
        '#weight' => -48,
      );
    }
    else {
      $form['public_prompt'] = array(
        '#type' => 'markup',
        '#markup' => t('These uploaded files will be publicly accessible'),
        '#weight' => -48,
      );
    }

    $node_upload_field_info = field_info_instance('node', 'field_uploaded_file', 'file');

    for ($i = 0; $i < 20; $i++) {
      $form['files']['file_upload_' . $i] = array(
        '#type' => 'managed_file',
        '#title' => t('Choose a file'),
        '#upload_location' => 'private://' . $node_upload_field_info['settings']['file_directory'] . '/',
        '#upload_validators' => array(
          'file_validate_extensions' => array($node_upload_field_info['settings']['file_extensions']),
        ),
      );
    }

    $form['add_more'] = array(
      '#type' => 'button',
      '#value' => t('Add More'),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Upload Files'),
    );

    $form['#validate'] = array('bulk_file_upload_add_files_form_validate');
    $form['#submit'] = array('bulk_file_upload_add_files_form_submit');
  }
  
  return $form;
  
}

/**
 * Validation handler.
 * Handles the validation for the bulk add files form.
 */
function bulk_file_upload_add_files_form_validate($form, &$form_state) {
  
  $term = taxonomy_term_load($form_state['values']['tid']);
  if ($term == FALSE || $term->vocabulary_machine_name != 'file_categories') {
    form_set_error('files', t('Error: You are trying to save these files under a restricted folder.'));
  }
}

/**
 * Submission handler.
 * Handles the submission for the bulk add files form.
 */
function bulk_file_upload_add_files_form_submit($form, &$form_state) {
  global $user;
  global $language;

  $new_file_node = (object) NULL;
  $new_file_node->type = 'file';
  $new_file_node->language = $language->language;
  $new_file_node->uid = $user->uid;
  $new_file_node->created = strtotime('now');
  $new_file_node->changed = strtotime('now');
  $new_file_node->status = 1;
  $new_file_node->comment = 1;
  $new_file_node->promote = 0;
  $new_file_node->moderate = 0;
  $new_file_node->sticky = 0;
  $new_file_node->validated = TRUE;
  $new_file_node->is_new = TRUE;
  $new_file_node->timestamp = strtotime('now');
  
  if (isset($form_state['values']['tid']) && ctype_digit($form_state['values']['tid'])) {
    $new_file_node->field_file_category['und'][0]['tid'] = $form_state['values']['tid'];
  }
   
  foreach ($form_state['values'] as $element_name => $value) {
    if (strpos($element_name, 'file_upload') !== FALSE && $value != 0) {
      if (isset($form_state['values']['is_private']) && $form_state['values']['is_private'] == 1) {
        if (isset($_SESSION['oa_space_id'])){
          $new_file_node->og_group_ref['und'][0]['target_id'] = $_SESSION['oa_space_id'];
          $new_file_node->og_group_ref['und'][0]['field_mode'] = 'default';
        }
        if (isset($_SESSION['oa_section_id'])){
          $new_file_node->oa_section_ref['und'][0]['target_id'] = $_SESSION['oa_section_id'];
        }
      }

      $saved_file = file_load($value);
      $saved_file_name = substr($saved_file->filename, 0, strrpos($saved_file->filename, '.'));
      $new_file_node->title = $saved_file_name;

      $new_file_node->field_uploaded_file['und'][0]['fid'] = $value;
      $new_file_node->field_uploaded_file['und'][0]['display'] = 1;
      
      node_save($new_file_node);
      unset($new_file_node->nid);
      unset($new_file_node->vid);
      
      drupal_set_message(t('You have successfully saved the file @filename', array('@filename' => $saved_file_name)));
    }
  }
}

/**
 * Helper function.
 * Renders the add new subfolder form. Will return an empty array if the user does not have permission to use the form.
 */
function bulk_file_upload_add_taxonomy_term_form($form, &$form_state, $parent_tid) {
  
  $form = array();
  
  if (user_access('access folder add form')) {
    
    $form['parent_tid'] = array(
      '#type' => 'hidden',
      '#value' => $parent_tid,
    );
    
    $parent_folder = taxonomy_term_load($parent_tid);
    $form['preamble'] = array(
      '#type' => 'markup',
      '#markup' => '<strong>' . t('Add a new folder within @folder_name', array('@folder_name' => $parent_folder->name)) . '</strong>',
    );
    
    $form['term_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Folder Name'),
      '#default_value' => '',
      '#required' => TRUE,
    );
    
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Add Folder'),
    );
    
    $form['#validate'] = array('bulk_file_upload_add_taxonomy_term_form_validate');
    $form['#submit'] = array('bulk_file_upload_add_taxonomy_term_form_submit');
  }
  
  return $form;
}

/**
 * Validation handler.
 * Handles the validation for the add taxonomy form.
 */
function bulk_file_upload_add_taxonomy_term_form_validate($form, &$form_state) {
  
  $term = taxonomy_term_load($form_state['values']['parent_tid']);
  if ($term == FALSE || $term->vocabulary_machine_name != 'file_categories') {
    form_set_error('term_name', t('Error: You are trying to add a folder under a restricted folder.'));
  }
}

/**
 * Submission handler.
 * Handles the validation for the add taxonomy form.
 */
function bulk_file_upload_add_taxonomy_term_form_submit($form, &$form_state) {
  
  $folder_vocab = taxonomy_vocabulary_machine_name_load('file_categories');
  
  $new_folder_term = (object) NULL;
  $new_folder_term->vid = $folder_vocab->vid;
  $new_folder_term->name = $form_state['values']['term_name'];
  $new_folder_term->parent = $form_state['values']['parent_tid'];
  $new_folder_term->vocabulary_machine_name = 'file_categories';
  
  $response = taxonomy_term_save($new_folder_term);
  
  if ($response == SAVED_NEW) {
    drupal_set_message(
      t(
        'You have successfully added the folder @folder_name', 
        array(
          '@folder_name' => $form_state['values']['term_name']
        )
      )
    );
  }
  else {
    drupal_set_message(t('Uh Oh. An error has occured and your new folder could not be added.'), 'error');
  }
}