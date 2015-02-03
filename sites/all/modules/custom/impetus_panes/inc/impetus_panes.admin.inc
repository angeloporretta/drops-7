<?php
/**
 * @file: Administrative forms and resources.
 */

/**
 * Form render function.
 * Renders the module's settings form.
 */
function impetus_panes_settings_form() {
  $form = array();
  
  $form['survey_gizmo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Survey Gizmo'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  
  $form['survey_gizmo']['impetus_panes_sg_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Survey Gizmo Email'),
    '#default_value' => variable_get('impetus_panes_sg_email', ''),
    '#required' => TRUE,
  );
  
  $form['survey_gizmo']['impetus_panes_sg_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Survey Gizmo Password'),
    '#default_value' => variable_get('impetus_panes_sg_password', ''),
    '#required' => TRUE,
  );
  
  $form = system_settings_form($form);
  return $form;
}

function impetus_master_settings_form($form , &$form_state) {
  $form = array();

  $form['#tree'] = TRUE;

  $form['bucket-name'] = array(
    '#type' => 'textfield',
    '#title' => t('Bucket Name'),
    '#default_value' => variable_get('bucket-name' , ''),
    '#required' => TRUE,
  );

  $form['bucket-position'] = array(
    '#type' => 'textfield',
    '#title' => t('Item position in the top menu'),
    '#default_value' => variable_get('bucket-position' , 1),
  );

  /* GROUP ACCESS - START */

  $form['bucket-access'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set group access'),
    '#prefix' => '<div id="bucket-groups-wrapper">',
    '#suffix' => '</div>',
  );
  $saved_groups = unserialize(variable_get('bucket-groups-access' , ''));

  if (empty($form_state['num_groups'])) {
       if (!empty($saved_groups)) {
         $form_state['num_groups'] = sizeof($saved_groups);
       } else {
        $form_state['num_groups'] = 1;
      }
    }
    for ($i = 0 ; $i < $form_state['num_groups'] ; $i++) {
      $form['bucket-access']['group'][$i] = array(
        '#type' => 'textfield',
        '#title' => t('Group Name'),
        '#autocomplete_path' => 'groups/autocomplete',
      );

      if (!empty($saved_groups[$i])) {
        $group = node_load($saved_groups[$i]);
        $form['bucket-access']['group'][$i]['#default_value'] = $group->title;
      }
    }

    $form['bucket-access']['add_more_groups'] = array(
      '#type' => 'submit',
      '#value' => t('Add more groups'),
      '#submit' => array('bucket_group_add_more_button'),
      '#ajax' => array(
        'callback' => 'bucket_ajax_callback',
        'wrapper' => 'bucket-groups-wrapper',
      ),
    );

    if ($form_state['num_groups'] > 1) {
      $form['bucket-access']['remove_group'] = array(
        '#type' => 'submit',
        '#value' => t('Remove group'),
        '#submit' => array('add_more_bucket_ajax_remove'),
        '#ajax' => array(
          'callback' => 'bucket_remove_ajax_callback',
          'wrapper' => 'bucket-groups-wrapper',
        ),
      );
    }

    /* GROUP ACCESS - END */

    /* USER ACCESS - START */

    $form['bucket-user-access'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set user access'),
    '#prefix' => '<div id="bucket-user-groups-wrapper">',
    '#suffix' => '</div>',
  );

    $saved_users = unserialize(variable_get('bucket-user-access' , ''));

  if (empty($form_state['num_users'])) {
       if (!empty($saved_users)) {
         $form_state['num_users'] = sizeof($saved_users);
       } else {
        $form_state['num_users'] = 1;
      }
    }

    for ($i = 0 ; $i < $form_state['num_users'] ; $i++) {
      $form['bucket-user-access']['user'][$i] = array(
        '#type' => 'textfield',
        '#title' => t('User Name'),
        '#autocomplete_path' => 'user/autocomplete',
      );

      if (!empty($saved_users[$i])) {
        $user = user_load($saved_users[$i]);
        $form['bucket-user-access']['user'][$i]['#default_value'] = $user->name;
      }
    }

    $form['bucket-user-access']['add_more_users'] = array(
      '#type' => 'submit',
      '#value' => t('Add more users'),
      '#submit' => array('bucket_user_add_more_button'),
      '#ajax' => array(
        'callback' => 'bucket_user_ajax_callback',
        'wrapper' => 'bucket-user-groups-wrapper',
      ),
    );

    if ($form_state['num_users'] > 1) {
      $form['bucket-user-access']['remove_user'] = array(
        '#type' => 'submit',
        '#value' => t('Remove user'),
        '#submit' => array('add_more_bucket_user_ajax_remove'),
        '#ajax' => array(
          'callback' => 'bucket_user_remove_ajax_callback',
          'wrapper' => 'bucket-user-groups-wrapper',
        ),
      );
    }

    /* USER ACCESS - END */
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function bucket_group_add_more_button($form , &$form_state) {
    if (!isset($form_state['num_groups'])) {
      $form_state['num_groups'] = 0;
      $form_state['num_groups']++;
    }
    $form_state['num_groups']++;
    $form_state['rebuild'] = TRUE;
  }

   function bucket_ajax_callback($form , $form_state) {
    return $form['bucket-access'];
  }

  function add_more_bucket_ajax_remove($form , &$form_state) {
    $form_state['num_groups']--;
    $form_state['rebuild'] = TRUE;
  }

  function bucket_remove_ajax_callback($form , &$form_state) {
    return $form['bucket-access'];
  }

  function bucket_user_add_more_button($form , &$form_state) {
    if (!isset($form_state['num_users'])) {
      $form_state['num_users'] = 0;
      $form_state['num_users']++;
    }
    $form_state['num_users']++;
    $form_state['rebuild'] = TRUE;
  }

  function bucket_user_ajax_callback($form , $form_state) {
    return $form['bucket-user-access'];
  }

  function add_more_bucket_user_ajax_remove($form , &$form_state) {
    $form_state['num_users']--;
    $form_state['rebuild'] = TRUE;
  }

  function bucket_user_remove_ajax_callback($form , &$form_state) {
    return $form['bucket-user-access'];
  }

  function impetus_master_settings_form_submit($form , &$form_state) {

    variable_set('bucket-name' , $form_state['input']['bucket-name']);
    variable_set('bucket-position' , $form_state['input']['bucket-position']);
    $group_list = array();
    foreach ($form_state['values']['bucket-access']['group'] as $groups) {
      $group_list[] = get_node_by_name($groups);
    }
    variable_set('bucket-groups-access' , serialize($group_list));

    $user_list = array();
    foreach($form_state['values']['bucket-user-access']['user'] as $user) {
      $user = user_load_by_name($user);
      $user_list[] = $user->uid;
    }
    variable_set('bucket-user-access' , serialize($user_list));
  }