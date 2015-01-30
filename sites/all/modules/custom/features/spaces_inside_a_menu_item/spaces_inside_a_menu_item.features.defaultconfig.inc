<?php
/**
 * @file
 * spaces_inside_a_menu_item.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function spaces_inside_a_menu_item_defaultconfig_features() {
  return array(
    'spaces_inside_a_menu_item' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function spaces_inside_a_menu_item_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'node-oa_space-field_display_in_top_menu'.
  $fields['node-oa_space-field_display_in_top_menu'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_display_in_top_menu',
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
    ),
    'field_instance' => array(
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
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Check this to display this space in the widget menu');
  t('Display in widget menu');

  return $fields;
}
