<?php
/**
 * @file
 * add_points_and_badges_view.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function add_points_and_badges_view_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_badges_imagecache';
  $strongarm->value = 'thumbnail';
  $export['user_badges_imagecache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_badges_list_show_users';
  $strongarm->value = '0';
  $export['user_badges_list_show_users'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_badges_nobadges';
  $strongarm->value = '';
  $export['user_badges_nobadges'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_badges_selector_type';
  $strongarm->value = '1';
  $export['user_badges_selector_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_badges_showblocked';
  $strongarm->value = '0';
  $export['user_badges_showblocked'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_badges_showone';
  $strongarm->value = '0';
  $export['user_badges_showone'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_badges_userweight';
  $strongarm->value = '0';
  $export['user_badges_userweight'] = $strongarm;

  return $export;
}
