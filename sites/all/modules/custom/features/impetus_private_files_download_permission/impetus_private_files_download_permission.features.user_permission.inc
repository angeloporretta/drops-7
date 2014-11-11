<?php
/**
 * @file
 * impetus_private_files_download_permission.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function impetus_private_files_download_permission_user_default_permissions() {
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
