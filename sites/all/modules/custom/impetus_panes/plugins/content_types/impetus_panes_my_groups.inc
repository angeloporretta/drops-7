<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('My Groups'),
  'description' => t('Links to groups the user is in. This will not appear for administrators and impetus admins.'),
  'category' => t('Impetus'),
  'edit form' => 'impetus_panes_my_groups_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_my_groups_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_my_groups_custom_pane_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 * Notice, the magic that automatically does that for you.
 */
function impetus_panes_my_groups_custom_pane_edit_form_submit(&$form, &$form_state) {
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function impetus_panes_my_groups_custom_pane_render($subtype, $conf, $args, $contexts) {
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  global $user;
  $block_html = '<ul class="my-groups-token">';

  if ($user->uid != 1 && !in_array('impetus admin', $user->roles) && !in_array('administrator', $user->roles) && property_exists($user, 'og_user_node')) {

    $node_links = array();
    foreach ($user->og_user_node['und'] as $nid) {

      $group_node = node_load($nid['target_id']);
      $node_links[$group_node->title] = drupal_get_path_alias('node/' . $group_node->nid);
    }

    foreach ($node_links as $group_title => $group_url_alias) {

      $block_html .= '<li><a href="/' . $group_url_alias . '">' . $group_title . '</a></li>';
    }
  }

  $block_html .= '</ul>';
  $block->content = $block_html;

  return $block;
}