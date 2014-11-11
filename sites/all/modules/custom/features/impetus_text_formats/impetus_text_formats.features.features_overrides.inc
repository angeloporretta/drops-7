<?php
/**
 * @file
 * impetus_text_formats.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function impetus_text_formats_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.full_html.filters|pathologic"] = array(
    'settings' => array(
      'local_paths' => '//dev-impetus-staging.pantheon.io
      //test-impetus-staging.pantheon.io',
      'protocol_style' => 'proto-rel',
    ),
    'status' => 1,
    'weight' => 50,
  );

 return $overrides;
}
