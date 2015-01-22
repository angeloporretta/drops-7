<?php
/**
 * @file
 * dragndrop_upload_feature.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function dragndrop_upload_feature_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_drag_and_drop_upload'
  $field_bases['field_drag_and_drop_upload'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_drag_and_drop_upload',
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
