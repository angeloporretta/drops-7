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
  if (is_numeric(arg(1))) {
    $node = node_load(arg(1));
    $section_id = $node->oa_section_ref[LANGUAGE_NONE][0]['target_id'];
    $setting = db_select('leaderboard_points', 'l')
      ->fields('l')
      ->condition('lid', $section_id, '=')
      ->execute()
      ->fetchAssoc();
    if (!empty($setting['points_category'])) {
      $view = views_embed_view('user_points_and_badges', 'page_2' , $setting['points_category'], $argument);
    }
  }
  
  $block->content = render($view);
  return $block;
}

function group_leaderboard_edit($form , &$form_state) {
  $nid = $form_state['contexts']['panelizer']->argument;
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

  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );

  return $form;
}

function group_leaderboard_edit_submit(&$form, &$form_state) {
  if (!empty($form_state['values'])) {
    foreach ($form_state['values'] as $form_key => $value) {
      $form_state['conf'][$form_key] = $value;
    }
  }
  $nid = $form_state['input']['nid'];
  $node = node_load($nid);
  $section_id = $node->oa_section_ref[LANGUAGE_NONE][0]['target_id'];
  $setting = db_select('leaderboard_points', 'l')
    ->fields('l')
    ->condition('lid', $section_id, '=')
    ->execute()
    ->fetchAssoc();

  if (!empty($setting)) {
    $category = $setting['points_category'];
  } else {
    $term = new stdClass();
    $term->name = $node->title;
    $term->vid = 5;
    taxonomy_term_save($term);

    db_insert('leaderboard_points')
      ->fields(array(
        'lid' => $section_id,
        'points_category' => $term->tid,
      ))
      ->execute();
  }
} 