<?php

// Plugin definition
$plugin = array(
  'single' => TRUE,
  'title' => t('Webform table'),
  'description' => t('Adds a configurable webform table'),
  'category' => t('Impetus'),
  'render callback' => 'webform_table_render',
  'edit form' => 'webform_table_edit',
  'all contexts' => TRUE,
);

/**
 * Render callback.
 */
function webform_table_render($subtype, $conf, $args, $contexts) {
  $block = new stdClass();
  $output = '';
  if (isset($conf['node'])) {
    $nid = $conf['node'];
    $node = node_load($nid);
    $output .= l(t("Edit report"), 'node/' . $nid . "/edit");
    $output .= drupal_render(node_view($node, 'full'));
  }
  $block->content = $output;
  return $block;
}

function webform_table_edit($form , &$form_state) {
  $form['node'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform'),
    '#default_value' => isset($form_state['conf']['node']) ? $form_state['conf']['node'] : '',
    '#required' => TRUE,
    '#autocomplete_path' => 'webform_report/autocomplete',
  );

  return $form;
}

function webform_table_edit_submit($form, &$form_state) {
  if (!empty($form_state['values'])) {
    foreach ($form_state['values'] as $form_key => $value) {
      $form_state['conf'][$form_key] = $value;
    }
  }
}

