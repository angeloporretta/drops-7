<?php
/**
 * @file
 * webform_report_export.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function webform_report_export_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
