<?php
/**
 * @file
 * impetus_text_formats.features.inc
 */

/**
 * Implements hook_filter_default_formats_alter().
 */
function impetus_text_formats_filter_default_formats_alter(&$data) {
  if (isset($data['full_html'])) {
    $data['full_html']['filters']['pathologic'] = array(
      'settings' => array(
        'local_paths' => '//dev-impetus-staging.pantheon.io
        //test-impetus-staging.pantheon.io',
        'protocol_style' => 'proto-rel',
      ),
      'status' => 1,
      'weight' => 50,
    ); /* WAS: '' */
  }
}
