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
  
  $section_options = array();
  
  $section_query = new EntityFieldQuery();
  $section_result = $section_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'oa_section')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('title', 'ASC')
    ->execute();
  
  if (!empty($section_result)) {
    $section_nodes = node_load_multiple(array_keys($section_result['node']));
    foreach ($section_nodes as $nid => $section_node) {
      $section_options[$nid] = $section_node->title;
    }
  }
  
  $form['section'] = array(
    '#type' => 'select',
    '#title' => t('Section'),
    '#required' => TRUE,
    '#prefix' => '<div id="announcements_section_field">',
    '#suffix' => '</div>',
    '#default_value' => $form_state['conf']['section'],
    '#options' => $section_options,
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
    ->fieldCondition('oa_section_ref', 'target_id', $conf['section'], '=')
    ->propertyOrderBy('created', 'DESC')
    ->execute();
  
  if (!empty($results)) {
    foreach ($results['node'] as $result) {
      $block->content .= render(node_view(node_load($result->nid), 'teaser'));
    }
  }

  return $block;
}
