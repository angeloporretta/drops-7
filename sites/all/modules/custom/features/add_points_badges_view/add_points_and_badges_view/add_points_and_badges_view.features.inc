<?php
/**
 * @file
 * add_points_and_badges_view.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function add_points_and_badges_view_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function add_points_and_badges_view_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
