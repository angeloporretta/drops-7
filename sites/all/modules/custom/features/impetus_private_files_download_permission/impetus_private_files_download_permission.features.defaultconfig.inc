<?php
/**
 * @file
 * impetus_private_files_download_permission.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function impetus_private_files_download_permission_defaultconfig_features() {
  return array(
    'impetus_private_files_download_permission' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function impetus_private_files_download_permission_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer private files download permission'.
  $permissions['administer private files download permission'] = array(
    'name' => 'administer private files download permission',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'private_files_download_permission',
  );

  // Exported permission: 'bypass private files download permission'.
  $permissions['bypass private files download permission'] = array(
    'name' => 'bypass private files download permission',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'private_files_download_permission',
  );

  return $permissions;
}
