<?php
/**
 * @file
 * add_points_and_badges_view.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function add_points_and_badges_view_taxonomy_default_vocabularies() {
  return array(
    'userpoints' => array(
      'name' => 'Userpoints',
      'machine_name' => 'userpoints',
      'description' => 'Automatically created by the userpoints module',
      'hierarchy' => 1,
      'module' => 'userpoints',
      'weight' => 0,
    ),
  );
}
