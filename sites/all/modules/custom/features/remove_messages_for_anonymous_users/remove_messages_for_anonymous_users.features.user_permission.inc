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

  // Exported permission: 'exclude from message filtering'.
  $permissions['exclude from message filtering'] = array(
    'name' => 'exclude from message filtering',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'disable_messages',
  );

  // Exported permission: 'view error messages'.
  $permissions['view error messages'] = array(
    'name' => 'view error messages',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'editor' => 'editor',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'disable_messages',
  );

  // Exported permission: 'view status messages'.
  $permissions['view status messages'] = array(
    'name' => 'view status messages',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'editor' => 'editor',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'disable_messages',
  );

  // Exported permission: 'view warning messages'.
  $permissions['view warning messages'] = array(
    'name' => 'view warning messages',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'editor' => 'editor',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'disable_messages',
  );

  return $permissions;
}
