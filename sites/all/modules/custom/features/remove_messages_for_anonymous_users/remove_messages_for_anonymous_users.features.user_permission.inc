<?php
/**
 * @file
 * remove_messages_for_anonymous_users.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function remove_messages_for_anonymous_users_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'view error messages'.
  $permissions['view error messages'] = array(
    'name' => 'view error messages',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'editor' => 'editor',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'disable_messages',
  );

  return $permissions;
}
