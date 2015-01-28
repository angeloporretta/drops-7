<?php
/**
 * @file
 * dummy_links.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function dummy_links_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_dummy_content'
  $field_bases['field_dummy_content'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_dummy_content',
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
