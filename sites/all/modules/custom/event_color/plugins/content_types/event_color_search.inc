<?php
// Plugin definition
$plugin = array(
  'single' => TRUE,
  // Title and description of the plugin
  'title' => t('Search form '),
  'description' => t('Search form'),
  'category' => t('Widgets'),
  // Define a theme function for this plugin
  'render callback' => 'event_color_render',
  'edit form' => 'event_color_edit',
  'all contexts' => TRUE, 
);

function event_color_render($subtype, $conf, $args, $contexts) {
  $block = new stdClass();

  $form = drupal_get_form('event_color_form');

  $block->content = render($form);
  $block->subject = t('Test');
  return $block;
}

function event_color_edit($form , &$form_state) {
  $conf = $form_state['conf'];
  $form['#tree'] = TRUE;
  ctools_form_include($form_state, 'content');
  ctools_form_include($form_state, 'event_color_search', 'event_color_search', 'plugins/content_types/event_color_search');

  $form['color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set your names for the color codes'),
    '#attributes' => array(
      'style' => 'clear:both',
    ),
  );

  $form['color']['FCE1E1'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#FCE1E1;">Set the name for this code:#FCE1E1</span>',
    '#default_value' => empty($conf['color']['FCE1E1']) ? '#FCE1E1' : $conf['color']['FCE1E1'],
  );

  $form['color']['E1FCFC'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#E1FCFC;">Set the name for this code:#E1FCFC</span>',
    '#default_value' => empty($conf['color']['E1FCFC']) ? '#E1FCFC' : $conf['color']['E1FCFC'],
  );

  $form['color']['BFFFE1'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#BFFFE1;">Set the name for this code:#BFFFE1</span>',
    '#default_value' => empty($conf['color']['BFFFE1']) ? '#BFFFE1' : $conf['color']['BFFFE1'],
  );

  $form['color']['D7FCC0'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#D7FCC0;">Set the name for this code:#D7FCC0</span>',
    '#default_value' => empty($conf['color']['D7FCC0']) ? '#D7FCC0' : $conf['color']['D7FCC0'],
  );

  $form['color']['F7FCC0'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#F7FCC0;">Set the name for this code:#F7FCC0</span>',
    '#default_value' => empty($conf['color']['F7FCC0']) ? '#F7FCC0' : $conf['color']['F7FCC0'],
  );

  $form['color']['F0C0FC'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#F0C0FC;">Set the name for this code:#F0C0FC</span>',
    '#default_value' => empty($conf['color']['F0C0FC']) ? '#F0C0FC' : $conf['color']['F0C0FC'],
  );

  $form['color']['BFDECE'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#BFDECE;">Set the name for this code:#BFDECE</span>',
    '#default_value' => empty($conf['color']['BFDECE']) ? '#BFDECE' : $conf['color']['BFDECE'],
  );

  $form['color']['BFD0DE'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#BFD0DE;">Set the name for this code:#BFD0DE</span>',
    '#default_value' => empty($conf['color']['BFD0DE']) ? '#BFD0DE' : $conf['color']['BFD0DE'],
  );

  $form['color']['D5BFDE'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#D5BFDE;">Set the name for this code:#D5BFDE</span>',
    '#default_value' => empty($conf['color']['D5BFDE']) ? '#D5BFDE' : $conf['color']['D5BFDE'],
  );

  $form['color']['DEBFBF'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#DEBFBF;">Set the name for this code:#DEBFBF</span>',
    '#default_value' => empty($conf['color']['DEBFBF']) ? '#DEBFBF' : $conf['color']['DEBFBF'],
  );

  $form['color']['FFD1AB'] = array(
    '#type' => 'textfield',
    '#prefix' => '<span style="margin-right:5px;background-color:#FFD1AB;">Set the name for this code:#FFD1AB</span>',
    '#default_value' => empty($conf['color']['FFD1AB']) ? '#FFD1AB' : $conf['color']['FFD1AB'],
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function event_color_edit_submit($form , &$form_state) {
  $form_state['conf']['color'] = $form_state['input']['color'];
}

?>