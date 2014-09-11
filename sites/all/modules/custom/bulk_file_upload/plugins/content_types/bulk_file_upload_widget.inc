<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Folder Widget'),
  'description' => t('Displays files and folders under a file folder.'),
  'category' => t('Impetus'),
  'edit form' => 'bulk_file_upload_pane_edit_form', 
  'render callback' => 'bulk_file_upload_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function bulk_file_upload_pane_edit_form($form, &$form_state) {
  
  $vocabulary = taxonomy_vocabulary_machine_name_load('file_categories');
  $tree = taxonomy_get_tree($vocabulary->vid);
  $options = array();
  
  foreach ($tree as $item) {
    $options[$item->tid] = str_repeat('-', $item->depth) . $item->name;
  }
 
  $form['file_category'] = array(
    '#type' => 'select',
    '#title' => t('Source Folder'),
    '#options' => $options,
    '#default_value' => $form_state['conf']['file_category'],
    '#required' => TRUE,
  );
  
  $form['show_subfolders'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Subfolders'),
    '#default_value' => (isset($form_state['conf']['show_subfolders'])) ? $form_state['conf']['show_subfolders'] : 1,
  );
  
  $form['show_add_subfolders'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Add Subfolders Form'),
    '#default_value' => (isset($form_state['conf']['show_add_subfolders'])) ? $form_state['conf']['show_add_subfolders'] : 1,
  );
  
  $form['show_add_files'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Add Files Form'),
    '#default_value' => (isset($form_state['conf']['show_add_files'])) ? $form_state['conf']['show_add_files'] : 1,
  );
  
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function bulk_file_upload_pane_edit_form_submit(&$form, &$form_state) {
  
  if (!empty($form_state['values'])) {
    foreach ($form_state['values'] as $form_key => $value) {
      $form_state['conf'][$form_key] = $value;
    }
  }
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info.
 */
function bulk_file_upload_pane_render($subtype, $conf, $args, $contexts) {
  
  if (isset($_SESSION['bulk_file_upload_breadcrumb'])) {
    unset($_SESSION['bulk_file_upload_breadcrumb']);
  }
  
  $_SESSION['bulk_file_upload_breadcrumb'] = array();
  
  array_push($_SESSION['bulk_file_upload_breadcrumb'], 
    array(
      'page_title' => drupal_get_title(),
      'path' => drupal_get_path_alias(current_path()),
      'tid' => '-1',
      'type' => 'base',
    )
  );
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';

  //if ($conf['show_subfolders'] == 1) {
  //  $block->content .= bulk_file_upload_render_child_folders($conf['file_category']);
  //}
  
  $block->content .= bulk_file_upload_render_file_table($conf['file_category']);
  
  if ($conf['show_add_subfolders'] == 1) {
    $block->content .= render(drupal_get_form('bulk_file_upload_add_taxonomy_term_form', $conf['file_category']));
  }
  
  if ($conf['show_add_files'] == 1) {
    $block->content .= render(drupal_get_form('bulk_file_upload_add_files_form', $conf['file_category']));
  }
  
  return $block;
}