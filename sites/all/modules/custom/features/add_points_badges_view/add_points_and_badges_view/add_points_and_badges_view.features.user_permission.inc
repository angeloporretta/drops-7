<?php
/**
 * @file
 * add_points_and_badges_view.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function add_points_and_badges_view_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access user badges'.
  $permissions['access user badges'] = array(
    'name' => 'access user badges',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'user_badges',
  );

  // Exported permission: 'add userpoints'.
  $permissions['add userpoints'] = array(
    'name' => 'add userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'administer userpoints'.
  $permissions['administer userpoints'] = array(
    'name' => 'administer userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'change badge assignments'.
  $permissions['change badge assignments'] = array(
    'name' => 'change badge assignments',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'user_badges',
  );

  // Exported permission: 'change own badge assignments'.
  $permissions['change own badge assignments'] = array(
    'name' => 'change own badge assignments',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'user_badges',
  );

  // Exported permission: 'edit userpoints'.
  $permissions['edit userpoints'] = array(
    'name' => 'edit userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'manage badges'.
  $permissions['manage badges'] = array(
    'name' => 'manage badges',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'user_badges',
  );

  // Exported permission: 'moderate userpoints'.
  $permissions['moderate userpoints'] = array(
    'name' => 'moderate userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'suppress badges in user profile'.
  $permissions['suppress badges in user profile'] = array(
    'name' => 'suppress badges in user profile',
    'roles' => array(
      'administrator' => 'administrator',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'user_badges',
  );

  // Exported permission: 'view own userpoints'.
  $permissions['view own userpoints'] = array(
    'name' => 'view own userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'view userpoints'.
  $permissions['view userpoints'] = array(
    'name' => 'view userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  return $permissions;
}
