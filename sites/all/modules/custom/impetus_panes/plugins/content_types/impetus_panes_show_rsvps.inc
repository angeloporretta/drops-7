<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Display RSVPs'),
  'description' => t('Shows RSVPs for a particular event.'),
  'category' => t('Open Atrium Events'),
  'edit form' => 'impetus_panes_show_rsvps_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_show_rsvps_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_show_rsvps_custom_pane_edit_form($form, &$form_state) {
  
  drupal_add_js(drupal_get_path('module', 'impetus_panes') . '/js/impetus_panes_show_rsvps.js');
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
      $options[$event_node->nid] = $event_node->title;
    }
  }
  
  $form['event'] = array(
    '#type' => 'select',
    '#title' => t('Event'),
    '#required' => TRUE,
    '#description' => t('The event whose RSVPs you want to display.'),
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
function impetus_panes_show_rsvps_custom_pane_edit_form_submit(&$form, &$form_state) {
  
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
function impetus_panes_show_rsvps_custom_pane_render($subtype, $conf, $args, $contexts) {
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  if (isset($conf['event'])) {
    
    $event_node = node_load($conf['event']);
  
    if ($event_node !== FALSE && $event_node->status != 0) {
      
      $block->title = t('RSVPs for the event @event_title.', array('@event_title' => $event_node->title));
      $block->content .= '<table class="show-rsvps">';
      
      $rsvps_results = db_select('event_rsvp_rsvps', 'e')
        ->fields('e', array('uid'))
        ->condition('e.nid', $event_node->nid, '=')
        ->execute()
        ->fetchAll();
      
      if (!empty($rsvps_results)) {
        
        $rsvp_uids = array();
        
        foreach ($rsvps_results as $rsvp_result) {
          $rsvp_uids[] = $rsvp_result->uid;
        }
        
        $rsvped_users = user_load_multiple($rsvp_uids);
        
        foreach ($rsvped_users as $rsvped_user) {
          $block->content .= '<tr><td>' . $rsvped_user->realname . '</td></tr>';
        }
      }
      else {
        $block->content .= '<tr><td>' . t('There are no RSVPs for this event.') . '</td></tr>';
      }
      
      $block->content .= '</table>';
    }
  }
  
  return $block;
}