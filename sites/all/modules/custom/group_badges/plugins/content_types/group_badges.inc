<?php

// Plugin definition
$plugin = array(
  'single' => TRUE,
  'title' => t('Group Leaderboard'),
  'description' => t('Display the leaderboard for the selected group'),
  'category' => t('Impetus'),
  'render callback' => 'group_leaderboard',
  'edit form' => 'group_leaderboard_edit',
  'all contexts' => TRUE,
);

/**
 * Render callback.
 */
function group_leaderboard($subtype, $conf, $args, $contexts) {
  $block = new stdClass();
  $argument = '';
  foreach ($conf['groups'] as $group) {
    if (empty($argument)) {
      $argument .= $group;
    } else {
      $argument .= '+' . $group;
    }
    
  }
  $view = views_embed_view('user_points_and_badges', 'page_1' , $argument);
  $block->content = render($view);
  return $block;
}

function group_leaderboard_edit($form , &$form_state) {
  $options = array();
  $groups = db_select('node' , 'n')
    ->fields('n' , array('nid' , 'title'))
    ->condition('type' , 'oa_group' , '=')
    ->orderBy('title')
    ->execute();

  foreach ($groups as $group) {
  	$options[$group->nid] = $group->title;
  }

  $form['groups'] = array(
  	'#type' => 'select',
    '#multiple' => TRUE,
  	'#title' => t('Select a group'),
  	'#options' => $options,
  	'#default_value' => $form_state['conf']['groups'],
  );

  return $form;
}

function group_leaderboard_edit_submit(&$form, &$form_state) {
  if (!empty($form_state['values'])) {
    foreach ($form_state['values'] as $form_key => $value) {
      $form_state['conf'][$form_key] = $value;
    }
  }
} 