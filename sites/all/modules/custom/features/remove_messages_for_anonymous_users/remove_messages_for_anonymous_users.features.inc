<?php
/**
 * @file
 * remove_messages_for_anonymous_users.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function remove_messages_for_anonymous_users_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
