<?php
/**
 * @file: Contains any page construction functions that this module uses.
 */

/**
 * Helper Function.
 * Renders the bulk add/remove groups from spaces page.
 */
function bulk_group_actions_render_space_page() {
  $html = render(drupal_get_form('bulk_group_actions_add_to_space_form'));
  $html .= render(drupal_get_form('bulk_group_actions_remove_from_space_form'));
  return $html;
}

/**
 * Helper Function.
 * Renders the bulk add/remove groups from sections page.
 */
function bulk_group_actions_render_section_page() {
  $html = render(drupal_get_form('bulk_group_actions_add_to_section_form'));
  $html .= render(drupal_get_form('bulk_group_actions_remove_from_section_form'));
  return $html;
}