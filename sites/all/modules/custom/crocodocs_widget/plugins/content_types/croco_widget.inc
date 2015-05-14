<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Crocodocs Widget'),
  'description' => t('Add the crocodocs viewer'),
  'category' => t('Impetus'),
  'render callback' => 'add_crocodocs',
  'edit form' => 'add_crocodocs_edit',
  'all contexts' => TRUE,
);

function add_crocodocs_edit($form , &$form_state) {
  $conf = $form_state['conf'];

  $form['croco_node'] = array(
  	'#type' => 'textfield',
  	'#title' => t('Select the crocodoc'),
  	'#default_value' => $conf['croco_node'],
  	'#autocomplete_path' => 'crocodocs/autocomplete',
  	'#required' => TRUE,
  );

  $form['submit'] = array(
  	'#type' => 'submit',
  	'#value' => t('Submit'),
  );

  return $form;
}

function add_crocodocs($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if (!empty($conf['croco_node'])) {
  	$node_title = $conf['croco_node'];
  	$node = load_croco_node_by_title($node_title);
    $node_render = node_view($node, 'full');
    if (isset($node_render['field_sadasdsa'])) {
      $block->content .= render($node_render['field_sadasdsa']);
    }
  }
  return $block;
}

function add_crocodocs_edit_submit(&$form, &$form_state) {
  if (!empty($form_state['values'])) {
    foreach ($form_state['values'] as $form_key => $value) {
      $form_state['conf'][$form_key] = $value;
    }
  }
}

function load_croco_node_by_title($title) {
  $node = db_select('node' , 'n')
    ->fields('n' , array('nid'))
    ->condition('title' , $title , '=')
    ->condition('type' , 'crocodoc' , '=')
    ->execute()
    ->fetchAssoc();

  $node_object = node_load($node['nid']);
  return $node_object;
}