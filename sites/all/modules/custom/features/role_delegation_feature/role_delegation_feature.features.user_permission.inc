<?php
/**
 * @file
 * role_delegation_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function role_delegation_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'assign all roles'.
  $permissions['assign all roles'] = array(
    'name' => 'assign all roles',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign comment moderator role'.
  $permissions['assign comment moderator role'] = array(
    'name' => 'assign comment moderator role',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign editor role'.
  $permissions['assign editor role'] = array(
    'name' => 'assign editor role',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'assign impetus admin role'.
  $permissions['assign impetus admin role'] = array(
    'name' => 'assign impetus admin role',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'role_delegation',
  );

  return $permissions;
}
