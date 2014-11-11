<?php
/**
 * @file
 * impetus_text_formats.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function impetus_text_formats_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format authenticated_html'.
  $permissions['use text format authenticated_html'] = array(
    'name' => 'use text format authenticated_html',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format custom_email_html'.
  $permissions['use text format custom_email_html'] = array(
    'name' => 'use text format custom_email_html',
    'roles' => array(
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'impetus admin' => 'impetus admin',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
