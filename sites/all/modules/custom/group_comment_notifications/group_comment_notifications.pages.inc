<?php
/**
 * @file: Includes page render functions for several pages that this module produces.
 */

/**
 * Form generation function.
 * In charge of rendering the form that saves comment notification settings per node.
 */
function group_comment_notifications_notification_settings_page($form, $form_state, $node) {
  
  $form = array();
  
  if ($node->comment == '2') {
    
    $group_options = array();
    $group_query = new EntityFieldQuery();
    $group_result = $group_query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'oa_group')
      ->propertyCondition('status', 1)
      ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->execute();

    if (!empty($group_result)) {
      $group_nodes = node_load_multiple(array_keys($group_result['node']));

      foreach ($group_nodes as $group_node) {
        $group_options[$group_node->nid] = $group_node->title;
      }
    }
    
    $default_options = db_select('group_comment_notifications_node_notifications_settings', 'n')
      ->fields('n', array('notification_setting_id', 'group_nid', 'frequency'))
      ->condition('content_nid', $node->nid)
      ->execute()
      ->fetchAllKeyed(1,2);

    $form['notification_groups'] = array(
      '#type' => 'select',
      '#title' => t('Notified Groups'),
      '#required' => TRUE,
      '#multiple' => TRUE,
      '#options' => $group_options,
      '#default_value' => (!empty($default_options)) ? array_keys($default_options) : '',
      '#empty_option' => ' - ' . t('Select a Group') . ' - ',
      '#empty_value' => '',
    );
    
    $form['notification_frequency'] = array(
      '#type' => 'select',
      '#title' => t('Notification Frequency'),
      '#required' => TRUE,
      '#options' => array(
        'immediately' => t('Immediately'),
      ),
      '#default_value' => (!empty($default_options)) ? reset($default_options) : '',
      '#empty_option' => ' - ' . t('Select a Frequency') . ' - ',
    );
    
    $form['nid'] = array(
      '#type' => 'hidden',
      '#value' => $node->nid,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save Notification Settings'),
    );

    $form['#submit'] = array('group_comment_notifications_notification_settings_page_submit');
  }
  else {
    $form['not_enabled_prompt'] = array(
      '#type' => 'markup',
      '#markup' => t('Comments have not been enabled for this piece of content. Please enable comments to access these settings.'),
    );
  }
  
  return $form;
}

/**
 * Form submission function.
 * Form submission function for the comment notification settings form.
 */
function group_comment_notifications_notification_settings_page_submit($form, $form_state) {
  
  db_delete('group_comment_notifications_node_notifications_settings')
    ->condition('content_nid', $form_state['values']['nid'])
    ->execute();
  
  $insert_query = db_insert('group_comment_notifications_node_notifications_settings')
    ->fields(array('content_nid', 'group_nid', 'frequency'));
  
  foreach ($form_state['values']['notification_groups'] as $group_nid) {
    $insert_query->values(array(
      'content_nid' => $form_state['values']['nid'],
      'group_nid' => $group_nid,
      'frequency' => $form_state['values']['notification_frequency'],
    ));
  }
  
  $success = $insert_query->execute();
  
  if ($success !== FALSE) {
    drupal_set_message(t('Comment notifications settings have been saved successfully.'), 'status', FALSE);
  }
}