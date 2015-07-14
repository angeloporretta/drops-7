<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Master Form'),
  'description' => t('Adds a master form'),
  'category' => t('Impetus'),
  'render callback' => 'add_master_form',
  'edit form' => 'edit_master_form',
  'all contexts' => TRUE,
);

function edit_master_form($form , &$form_state) {

  $conf = $form_state['conf'];

  $form['form_node'] = array(
  	'#type' => 'textfield',
  	'#title' => t('Select the form'),
  	'#default_value' => $conf['form_node'],
  	'#autocomplete_path' => 'webform/autocomplete',
  	'#required' => TRUE,
  );

  $form['form_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Filter by option'),
    '#default_value' => $conf['form_type'],
    '#required' => TRUE,
  );

  $form['submit'] = array(
  	'#type' => 'submit',
  	'#value' => t('Submit'),
  );

  return $form;
}

function edit_master_form_submit($form, &$form_state) {
  if (!empty($form_state['values'])) {
    foreach ($form_state['values'] as $form_key => $value) {
      $form_state['conf'][$form_key] = $value;
    }
  }
}

function add_master_form($subtype, $conf, $panel_args, $context) {
  $type = $conf['form_type'];
  $block = new stdClass();
  $block->content = '';
  if (!empty($conf['form_node'])) {
  	$node_title = $conf['form_node'];
  	$node = load_webform_node_by_title($node_title);
    foreach($node->webform['components'] as $key => $value) {
      if(strpos($value['extra']['css_classes'], "select-type-options") !== false) {
        $items = $node->webform['components'][$key]['extra']['items'];
        $items_array = explode("\n", $items);
        foreach ($items_array as $items_array_key => $item_array_value) {
          $items_array_values = explode("|", $item_array_value);
          if($items_array_values[1] == $type) {
            $default_value = $items_array_values[0];
            $default_key = $key;
          }
        }
      }
    }
    $node->title = '';
    $node->webform['components'][$key]['value'] = $default_value;
    // dsm($node);
    $node_render = node_view($node, 'full');
    unset($node_render['links']['print_mail']);
    unset($node_render['links']['print_pdf']);
    $block->content .= render($node_render);
  }
  return $block;
}