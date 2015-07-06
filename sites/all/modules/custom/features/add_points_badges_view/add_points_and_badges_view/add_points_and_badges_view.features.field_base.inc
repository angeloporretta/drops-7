<?php
/**
 * @file
 * add_points_and_badges_view.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function add_points_and_badges_view_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_add_points'
  $field_bases['field_add_points'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_add_points',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
