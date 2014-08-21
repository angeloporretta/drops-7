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
