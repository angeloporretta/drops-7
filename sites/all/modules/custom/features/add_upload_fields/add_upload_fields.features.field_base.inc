<?php
/**
 * @file
 * add_upload_fields.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function add_upload_fields_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_allow_file_upload'
  $field_bases['field_allow_file_upload'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_allow_file_upload',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
