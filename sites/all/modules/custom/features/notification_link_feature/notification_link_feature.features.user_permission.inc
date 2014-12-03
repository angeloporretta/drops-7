<?php
/**
 * @file
 * notification_link_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function notification_link_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format emailshtml'.
  $permissions['use text format emailshtml'] = array(
    'name' => 'use text format emailshtml',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
