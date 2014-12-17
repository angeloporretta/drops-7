<?php
/**
 * @file
 * remove_item_from_top_menu.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function remove_item_from_top_menu_flag_default_flags() {
  $flags = array();
  // Exported flag: "Remove node from top nav".
  $flags['remove_from_top_nav'] = array(
    'content_type' => 'node',
    'title' => 'Remove node from top nav',
    'global' => 1,
    'types' => array(
      0 => 'announcement',
      1 => 'panopoly_page',
      2 => 'video_discussion',
      3 => 'oa_discussion_post',
      4 => 'oa_wiki_page',
      5 => 'oa_event',
      6 => 'file',
      7 => 'oa_group',
      8 => 'oa_section',
      9 => 'oa_space',
      10 => 'oa_worktracker_task',
      11 => 'oa_team',
      12 => 'webform',
      13 => 'oa_ical_importer',
    ),
    'flag_short' => 'Remove from top nav',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Display in top nav',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 3,
        1 => 5,
      ),
      'unflag' => array(
        0 => 3,
        1 => 5,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'remove_item_from_top_menu',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
