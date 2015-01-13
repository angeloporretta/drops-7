<?php
/**
 * @file
 * amazon_file_field.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function amazon_file_field_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_upload_file_big_files'
  $field_bases['field_upload_file_big_files'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_upload_file_big_files',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'file',
    'settings' => array(
      'display_default' => 0,
      'display_field' => 0,
      'uri_scheme' => 's3',
    ),
    'translatable' => 0,
    'type' => 'file',
  );

  return $field_bases;
}
