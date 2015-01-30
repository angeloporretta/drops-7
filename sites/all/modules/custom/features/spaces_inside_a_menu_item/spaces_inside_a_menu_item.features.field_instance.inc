<?php
/**
 * @file
 * spaces_inside_a_menu_item.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function spaces_inside_a_menu_item_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-oa_space-field_display_in_top_menu'
  $field_instances['node-oa_space-field_display_in_top_menu'] = array(
    'bundle' => 'oa_space',
    'comment_alter' => 0,
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Check this to display this space in the widget menu',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 20,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_display_in_top_menu',
    'label' => 'Display in widget menu',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Check this to display this space in the widget menu');
  t('Display in widget menu');

  return $field_instances;
}
