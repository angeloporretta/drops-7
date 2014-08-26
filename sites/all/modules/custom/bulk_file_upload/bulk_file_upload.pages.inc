<?php
/**
 * @file: Defines all rendered output for pages this module uses.
 */

/**
 * Helper Function.
 * Renders the bulk upload page.
 */
function bulk_file_upload_render_upload_page() {
  
  return drupal_get_form('bulk_file_upload_add_files_form');
}

/*
 * Helper Function.
 * Renders the bulk download page.
 */
function bulk_file_upload_render_download_page() {

  if (isset($_GET['tid']) && ctype_digit($_GET['tid'])) {
    
    $file_folder = taxonomy_term_load($_GET['tid']);
    
    if ($file_folder !== FALSE && $file_folder->vocabulary_machine_name == 'file_categories') {
      
      $node_query = new EntityFieldQuery();
      $node_result = $node_query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'file')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_file_category', 'tid', $_GET['tid'])
        ->execute();
      
      if (!empty($node_result)) {

        $file_nodes = node_load_multiple(array_keys($node_result['node']));
        $archive_file = drupal_tempnam('./temp-download-archives','');
        $archive_name = str_replace(' ', '-', $file_folder->name . '.zip');
        $zip_archive = new ZipArchive();


        if ($zip_archive->open($archive_file, ZipArchive::CREATE) === TRUE) {
          foreach ($file_nodes as $file_node) {
            if (node_access('view', $file_node)) {
              $file_fields = field_get_items('node', $file_node, 'field_uploaded_file');
              $base_file_path = '.' . str_replace($_SERVER['DOCUMENT_ROOT'], '', drupal_realpath($file_fields[0]['uri']));
              $zip_archive->addFile($base_file_path, $file_fields[0]['filename']);
              watchdog('DEBUG_DOWNLOAD_FILES', 'Basepath: ' . $base_file_path . ' ---- New File Name: ' . $file_fields[0]['filename']);
            }
          }
          
          $zip_archive->close();
          header('Content-Type: application/zip');
          header('Content-disposition: attachment; filename=' . $archive_name);
          header('Content-Length: ' . filesize($archive_file));
          readfile($archive_file);
          exit();
        }
        else {
          drupal_set_message(t('Oops something went wrong! We cannot download all the files for you. Failed to create archive.'), 'error');
        }
      }
      else {
        drupal_set_message(t('Oops something went wrong! There are no files in this folder for you to download.'), 'warning');
      }
    }
    else {
      drupal_set_message(t('Oops something went wrong! The file folder with that id has not been found.'), 'error');
    }
  }
  else {
    drupal_set_message(t('Oops something went wrong! You are trying to download from an invalid folder id!'), 'error');
  }
  
  return '';
}