<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Event RSVP'),
  'description' => t('Generates an RSVP form for any event that you choose.'),
  'category' => t('Open Atrium Events'),
  'edit form' => 'impetus_panes_event_rsvp_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_event_rsvp_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_event_rsvp_custom_pane_edit_form($form, &$form_state) {
  
  $options = array();
  
  $field_query = new EntityFieldQuery();
  $results = $field_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'oa_event')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('title', 'ASC')
    ->execute();
  
  $options = array();
  
  if (!empty($results)) {
    $event_nodes = node_load_multiple(array_keys($results['node']));
    
    foreach ($event_nodes as $event_node) {
      if (event_rsvp_event_has_passed($event_node) == FALSE) {
        $options[$event_node->nid] = $event_node->title;
      }
    }
  }
  
  $form['event'] = array(
    '#type' => 'select',
    '#title' => t('Event'),
    '#required' => TRUE,
    '#description' => t('The event whose RSVP you want to allow.') . 
                      '<br/><strong>'  .
                      t('Note: You cannot select an event that has already passed.') . 
                      '</strong>',
    '#default_value' => $form_state['conf']['event'],
    '#empty_option' => '- ' . t('Select an Event') . ' -',
    '#empty_value' => '',
    '#options' => $options,
  );
  
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function impetus_panes_event_rsvp_custom_pane_edit_form_submit(&$form, &$form_state) {
  
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
function impetus_panes_event_rsvp_custom_pane_render($subtype, $conf, $args, $contexts) {
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  if (isset($conf['event'])) {
    
    $event_node = node_load($conf['event']);
  
    if ($event_node !== FALSE && $event_node->status != 0 && node_access('view', $event_node)) {
      $rsvp_form = drupal_get_form('event_rsvp_rsvp_form', $event_node->nid);
      
      if (isset($rsvp_form['event_rsvp_submit'])) {
        $rsvp_form['event_rsvp_submit']['#value'] = 
        $rsvp_form['event_rsvp_submit']['#value'] . ' ' . t('for @event_title', array('@event_title' => $event_node->title));
      }
      
      $block->content = render($rsvp_form);
    }
  }
  
  return $block;
}