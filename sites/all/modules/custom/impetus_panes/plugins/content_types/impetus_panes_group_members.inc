<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Group Members'),
  'description' => t('Links to groups the user is in. This will not appear for administrators and impetus admins.'),
  'category' => t('Impetus'),
  'edit form' => 'impetus_panes_group_members_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_group_members_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_group_members_custom_pane_edit_form($form, &$form_state) {
  
  $options = array();
  
  $field_query = new EntityFieldQuery();
  $results = $field_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'oa_group')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('title', 'ASC')
    ->execute();
  
  $group_nids = array();
  
  if (!empty($results)) {
    $group_nids = array_keys($results['node']);
  }
  
  $group_nodes = node_load_multiple($group_nids);

  foreach ($group_nodes as $nid => $node) {
    $options[$nid] = $node->title;
  }
  
  $form['group'] = array(
    '#type' => 'select',
    '#title' => t('Group members from which group?'),
    '#options' => $options,
    '#default_value' => $form_state['conf']['group'],
    '#required' => TRUE,
  );
  $form['include_children'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include child groups'),
    '#default_value' => (isset($form_state['conf']['include_children'])) ? $form_state['conf']['include_children'] : 1
  );
  
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function impetus_panes_group_members_custom_pane_edit_form_submit(&$form, &$form_state) {
  
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
function impetus_panes_group_members_custom_pane_render($subtype, $conf, $args, $contexts) {
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  $group_ids = array();
  $group_id = $conf['group'];
  $subgroups = og_subgroups_children_load('node', $group_id);

  drupal_add_css(drupal_get_path('module', 'impetus_panes') . '/css/impetus_panes_group_members.css');
  
  if ($conf['include_children'] == 1) {
    
    $subgroups = og_subgroups_children_load('node', $group_id);
    
    if (!empty($subgroups)) {
      $subgroup_nodes = node_load_multiple(array_keys($subgroups['node']));

      foreach ($subgroup_nodes as $subgroup_node) {
        if ($subgroup_node->type == 'oa_group') {
          $group_ids[] = $subgroup_node->nid; 
        }
      }
    }
  }
    
  $group_ids[] = $group_id;
  
  $users = array();
  $user_query = new EntityFieldQuery();
  $user_results = $user_query->entityCondition('entity_type', 'user')
    ->propertyCondition('status', 1)
    ->propertyCondition('uid', 1, '<>')
    ->fieldCondition('og_user_node', 'target_id', $group_ids, 'IN')
    ->propertyOrderBy('name', 'ASC')
    ->execute();
  
  if (!empty($user_results)) {
    $users = user_load_multiple(array_keys($user_results['user']));
    foreach ($users as $uid => $user) {
      if (in_array('impetus admin', $user->roles) || in_array('administrator', $user->roles)) {
        unset($users[$uid]);
      }
    }
  }
  
  foreach ($users as $user) {
    $real_name = (strlen($user->realname) > 0) ? $user->realname : $user->name;
    $block->content .= '<div class="impetus-panes-user">';
    $block->content .= oa_users_picture($user, 'thumbnail');
    $block->content .=  '<div class="impetus-panes-user-name">' . $real_name . '<br/>' .
                        '<a href="/messages/new?preset-message-uid=' . $user->uid . '&form-mod-redirection='. drupal_get_path_alias(current_path()) . '" rel="lightmodal[|height: 600px;]" class="mailto-link">' . t('Message Me') . '</a>' .
                        '</div>';
    $block->content .= '</div>';
  }

  return $block;
}