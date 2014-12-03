<?php
/**
 * @file
 * notification_link_feature.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function notification_link_feature_filter_default_formats() {
  $formats = array();

  // Exported format: EmailsHTML.
  $formats['emailshtml'] = array(
    'format' => 'emailshtml',
    'name' => 'EmailsHTML',
    'cache' => 0,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_tokens' => array(
        'weight' => -42,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
