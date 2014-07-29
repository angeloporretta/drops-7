<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Announcements'),
  'description' => t('Links to groups the user is in. This will not appear for administrators and impetus admins.'),
  'category' => t('Impetus'),
  'edit form' => 'impetus_panes_announcements_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_announcements_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_announcements_custom_pane_edit_form($form, &$form_state) {
  
  $options = array();
  
  $field_query = new EntityFieldQuery();
  $results = $field_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'oa_group')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('title', 'ASC')
    ->execute();
  
  $group_nids = array();
  
  if (!empty($results)) {
    foreach ($results['node'] as $result) {
      $group_nids[] = $result->nid;
    }
  }
  
  $group_nodes = node_load_multiple($group_nids);

  foreach ($group_nodes as $nid => $node) {
    $options[$nid] = $node->title;
  }
  
  $form['group'] = array(
    '#type' => 'select',
    '#title' => t('Announcements from which group?'),
    '#options' => $options,
    '#default_value' => $form_state['conf']['group'],
    '#required' => TRUE,
  );
  
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function impetus_panes_announcements_custom_pane_edit_form_submit(&$form, &$form_state) {
  
  if (!empty($form_state['values'])) {
    foreach ($form_state['values'] as $form_key => $value) {
      $form_state['conf'][$form_key] = $value;
    }
  }
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info.
 */
function impetus_panes_announcements_custom_pane_render($subtype, $conf, $args, $contexts) {
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  $field_query = new EntityFieldQuery();
  $results = $field_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'announcement')
    ->propertyCondition('status', 1)
    ->fieldCondition('og_group_ref', 'target_id', $conf['group'], '=')
    ->propertyOrderBy('created', 'DESC')
    ->execute();
  
  if (!empty($results)) {
    foreach ($results['node'] as $result) {
      $block->content .= render(node_view(node_load($result->nid), 'teaser'));
    }
  }

  return $block;
}