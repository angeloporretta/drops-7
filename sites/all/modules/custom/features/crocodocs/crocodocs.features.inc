<?php
/**
 * @file
 * crocodocs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function crocodocs_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function crocodocs_node_info() {
  $items = array(
    'crocodoc' => array(
      'name' => t('Crocodoc'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
