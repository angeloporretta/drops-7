<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Section Metrics'),
  'description' => t('Shows metrics of a particular section and group of mailchimp emails.'),
  'category' => t('Impetus'),
  'edit form' => 'impetus_panes_section_metrics_edit_form', 
  'render callback' => 'impetus_panes_section_metrics_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_section_metrics_edit_form($form, &$form_state) {
  
  
  $section_options = array();
  
  $section_field_query = new EntityFieldQuery();
  $section_results = $section_field_query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'oa_section')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('title', 'ASC')
    ->execute();
  
  if (!empty($section_results)) {
    $section_nodes = node_load_multiple(array_keys($section_results['node']));
    
    foreach ($section_nodes as $section_node) {
      $section_options[$section_node->nid] = $section_node->title;
    }
  }
  
  // Section Field.
  $form['section'] = array(
    '#type' => 'select',
    '#title' => t('Section'),
    '#required' => TRUE,
    '#description' => t('The section whose members metrics you want to display.'),
    '#default_value' => $form_state['conf']['section'],
    '#empty_option' => '- ' . t('Select a Section') . ' -',
    '#empty_value' => '',
    '#options' => $section_options,
    '#ajax' => array(
      'wrapper' => 'metrics-wrapper',
      'callback' => 'impetus_panes_section_metrics_files_ajax',
    )
  );
  
  // Fieldset Wrapper.
  $form['section_metrics'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metrics'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="metrics-wrapper">',
    '#suffix' => '</div>',
  );
  
  // File Field.
  $files_options = array();
  
  if (!empty($form['section']['#default_value'])) {
    
    $files_field_query = new EntityFieldQuery();
    $file_results = $files_field_query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'file')
      ->fieldCondition('oa_section_ref', 'target_id', $form['section']['#default_value'], '=')
      ->propertyOrderBy('title', 'ASC')
      ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->execute();

    if (!empty($file_results)) {
      $file_nodes = node_load_multiple(array_keys($file_results['node']));
      foreach($file_nodes as $file_node) {
        $files_options[$file_node->nid] = $file_node->title;
      }
    }
  }
  
  $form['section_metrics']['files'] = array(
    '#type' => 'select',
    '#title' => t('Files to Track'),
    '#multiple' => TRUE,
    '#description' => t('The file downloads you want to track.'),
    '#validated' => TRUE,
    '#default_value' => $form_state['conf']['files'],
    '#empty_option' => '- ' . t('Select Files to Track') . ' -',
    '#empty_value' => '',
    '#options' => $files_options,
  );
  
  // Conversation field.
  $conversation_options = array();
  
  if (!empty($form['section']['#default_value'])) {
    
    $conversation_node_query = new EntityFieldQuery();
    $conversation_node_results = $conversation_node_query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', array('panopoly_page', 'video_discussion'), 'IN')
      ->fieldCondition('oa_section_ref', 'target_id', $form['section']['#default_value'], '=')
      ->propertyOrderBy('title', 'ASC')
      ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->execute();

    if (!empty($conversation_node_results)) {
      $conversation_nodes = node_load_multiple(array_keys($conversation_node_results['node']));
      foreach($conversation_nodes as $conversation_node) {
        $conversation_options[$conversation_node->nid] = $conversation_node->title;
      }
    }
  }
  
  $form['section_metrics']['conversation_nodes'] = array(
    '#type' => 'select',
    '#title' => t('Conversations on Pages'),
    '#multiple' => TRUE,
    '#description' => t('Pages whose conversations you want to display.'),
    '#validated' => TRUE,
    '#default_value' => $form_state['conf']['conversation_nodes'],
    '#empty_option' => '- ' . t('Select Page Conversations to Track') . ' -',
    '#empty_value' => '',
    '#options' => $conversation_options,
  );
  
  // Mailchimp Lists Field.
  $mailchimp_library_path = libraries_get_path('mailchimp');
  require_once $mailchimp_library_path . '/src/Mailchimp.php';
  
  $campaign_options = db_select('impetus_panes_mailchimp_campaigns', 'm')
    ->fields('m', array('campaign_id', 'campaign_title'))
    ->execute()
    ->fetchAllKeyed(0,1);
  
  $form['section_metrics']['mailchimp_campaigns'] = array(
    '#type' => 'select',
    '#title' => t('Mailchimp Campaigns'),
    '#multiple' => TRUE,
    '#description' => t('Campaigns whose user metrics you want to display.'),
    '#validated' => TRUE,
    '#default_value' => $form_state['conf']['mailchimp_campaigns'],
    '#empty_option' => '- ' . t('Select Mailchimp Campaigns') . ' -',
    '#empty_value' => '',
    '#options' => $campaign_options,
  );
  
  // Survey Gizmo Field.
  $survey_options = db_select('impetus_panes_survey_gizmo_surveys', 's')
    ->fields('s', array('survey_id', 'survey_title'))
    ->execute()
    ->fetchAllKeyed(0, 1);
  
  $form['section_metrics']['survey_gizmo_surveys'] = array(
    '#type' => 'select',
    '#title' => t('Survey Gizmo Surveys'),
    '#multiple' => TRUE,
    '#description' => t('Survey Gizmo surveys whose metrics you want to display.'),
    '#validated' => TRUE,
    '#default_value' => $form_state['conf']['survey_gizmo_surveys'],
    '#empty_option' => '- ' . t('Select Surveys') . ' -',
    '#empty_value' => '',
    '#options' => $survey_options,
  );
  
  ctools_form_include($form_state, 'content');
  ctools_form_include(
    $form_state, 
    'impetus_panes_section_metrics', 
    'impetus_panes', 
    'plugins/content_types'
  );
  
  return $form;
}

/**
 * Ajax handler.
 * Handler for when the section select box is changed.
 */
function impetus_panes_section_metrics_files_ajax($form, $form_state) {
  
  if (isset($form_state['values']['section']) && $form_state['values']['section'] != '') {
    
    // Update the options of the file field.
    $file_options = array();
    
    $files_field_query = new EntityFieldQuery();
    $file_results = $files_field_query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'file')
      ->fieldCondition('oa_section_ref', 'target_id', $form_state['values']['section'], '=')
      ->propertyOrderBy('title', 'ASC')
      ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->execute();
    
    if (!empty($file_results)) {
      $file_nodes = node_load_multiple(array_keys($file_results['node']));
      foreach($file_nodes as $file_node) {
        $file_options[$file_node->nid] = $file_node->title;
      }
    }
    
    $form['section_metrics']['files']['#validated'] = TRUE;
    $form['section_metrics']['files']['#options'] = $file_options;
    
    // Update the options of the conversations field.
    $conversation_options = array();
    
    $conversation_node_query = new EntityFieldQuery();
    $conversation_node_results = $conversation_node_query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', array('panopoly_page', 'video_discussion'), 'IN')
      ->fieldCondition('oa_section_ref', 'target_id', $form_state['values']['section'], '=')
      ->propertyOrderBy('title', 'ASC')
      ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->execute();

    if (!empty($conversation_node_results)) {
      $conversation_nodes = node_load_multiple(array_keys($conversation_node_results['node']));
      foreach($conversation_nodes as $conversation_node) {
        $conversation_options[$conversation_node->nid] = $conversation_node->title;
      }
    }
    
    $form['section_metrics']['conversation_nodes']['#validated'] = TRUE;
    $form['section_metrics']['conversation_nodes']['#options'] = $conversation_options;
  }
  
  return $form['section_metrics'];
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function impetus_panes_section_metrics_edit_form_submit(&$form, &$form_state) {
  
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
function impetus_panes_section_metrics_render($subtype, $conf, $args, $contexts) {
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  if (isset($conf['section'])) {
    drupal_add_css(drupal_get_path('module', 'impetus_panes') . '/css/impetus_panes_section_metrics.css');
    $users = array();
    $section_node = node_load($conf['section']);
    $related_groups = field_get_items('node', $section_node, 'field_oa_group_ref');

    if ($related_groups !== FALSE) {
      
      $related_group_ids = array();
      foreach($related_groups as $related_group) {
        $related_group_ids[] = $related_group['target_id'];
      }
      
      $user_query = new EntityFieldQuery();
      $user_results = $user_query->entityCondition('entity_type', 'user')
        ->propertyCondition('status', 1)
        ->propertyCondition('uid', 1, '<>')
        ->fieldCondition('og_user_node', 'target_id', $related_group_ids, 'IN')
        ->propertyOrderBy('name', 'ASC')
        ->execute();
      
      if (!empty($user_results)) {
        $users = user_load_multiple(array_keys($user_results['user']));
      }
      
      $file_nids = array_keys($conf['files']);
      $comment_nids = array_keys($conf['conversation_nodes']);
      
      foreach ($users as $uid => $loaded_user) {
        if (!in_array('administrator', $loaded_user->roles) && !in_array('impetus admin', $loaded_user->roles) && $loaded_user->uid != '1') {
          
          if (!empty($file_nids)) {
            $users[$uid]->file_download_nodes = impetus_panes_section_metrics_get_file_downloads($loaded_user, $file_nids);
          }
          
          if (!empty($comment_nids)) {
            $users[$uid]->comments = impetus_panes_section_metrics_get_comments($loaded_user, $comment_nids);
          }
        }
        else {
          unset($users[$uid]);
        }
      }
    }
    
    $block->content = impetus_panes_section_metrics_render_body($conf, $users);
  }
  
  return $block;
}

/**
 * Helper function.
 * Finds the most recent download records of files that belong to a particular section.
 * @param object $loaded_user: A user object of the user whose downloads you want to track.
 * @param array $file_node_nids: An array of file nodes.
 * @return array: An array of file download records.
 */
function impetus_panes_section_metrics_get_file_downloads($loaded_user, $file_node_nids) {
  
  $user_download_records = file_tracker_get_file_node_downloads(
    array(
      'uids' => array($loaded_user->uid),
      'nids' => $file_node_nids,
    ), 
    'nid', 
    TRUE
  );
  $file_download_nodes = array();
  $file_download_nids = array();

  foreach ($user_download_records as $user_download_record) {
    $file_download_nids[] = $user_download_record->nid;
  }

  $file_download_nodes = node_load_multiple($file_download_nids);
  ksort($file_download_nodes);
  
  return $file_download_nodes;
}

/**
 * Helper Function.
 * Helps format comments in a particular way.
 * @param object $loaded_user: A drupal user object
 * @param array $comment_nids: An array of node IDs whose comments you want.
 * @return array: An array of formatted comments.
 */
function impetus_panes_section_metrics_get_comments($loaded_user, $comment_nids) {

  $formatted_comments = array();
  $comments = array();
  $comment_query = new EntityFieldQuery();
  $comment_results = $comment_query->entityCondition('entity_type', 'comment')
    ->propertyCondition('uid', $loaded_user->uid)
    ->propertyCondition('nid', $comment_nids, 'IN')
    ->propertyCondition('status', 1)
    ->execute();

  if (!empty($comment_results)) {
    $comments = comment_load_multiple(array_keys($comment_results['comment']));
    foreach ($comments as $comment) {
      $formatted_comments[$comment->nid][] = $comment;
    }
  }
  
  ksort($formatted_comments);
  return $formatted_comments;
}

/**
 * Helper function.
 * @param array $configurations: The $conf array provided to you as a parameter by pane render functions.
 * @param array $users: An array of users.
 * @return string: The HTML structure of the rendered pane.
 */
function impetus_panes_section_metrics_render_body($configurations, $users) {
  
  $tracked_file_nodes = array();
  $tracked_commented_nodes = array();
  $tracked_mailchimp_campaigns = array();
  $tracked_surveys = array();
  
  if (isset($configurations['files']) && !empty($configurations['files'])) {
    $tracked_file_nodes = node_load_multiple(array_keys($configurations['files']));
    ksort($tracked_file_nodes);
  }
  
  if (isset($configurations['conversation_nodes']) && !empty($configurations['conversation_nodes'])) {
    $tracked_commented_nodes = node_load_multiple(array_keys($configurations['conversation_nodes']));
    ksort($tracked_commented_nodes);
  }
  
  if (isset($configurations['mailchimp_campaigns']) && !empty($configurations['mailchimp_campaigns'])) {
    $tracked_mailchimp_campaigns = db_select('impetus_panes_mailchimp_campaigns', 'm')
      ->fields('m', array('campaign_id', 'campaign_title'))
      ->condition('campaign_id', $configurations['mailchimp_campaigns'], 'IN')
      ->execute()
      ->fetchAllKeyed();
  }
  
  if (isset($configurations['survey_gizmo_surveys']) && !empty($configurations['survey_gizmo_surveys'])) {
    $tracked_surveys = db_select('impetus_panes_survey_gizmo_surveys', 's')
      ->fields('s', array('survey_id', 'survey_title'))
      ->condition('survey_id', $configurations['survey_gizmo_surveys'], 'IN')
      ->execute()
      ->fetchAll();
  }
  
  $pane_body = '<table class="metrics-table">';
  $pane_body .= '<thead><tr><th>' . t('First Name') . '</th><th>' . t('Last Name') . '</th>';
  
  // File tracker downloads headings.
  foreach ($tracked_file_nodes as $tracked_file_node) {
    $pane_body .= '<th>' . t('Download tracking for') . ':<br/><a href="/' . drupal_get_path_alias('node/' . $tracked_file_node->nid) . '" target="_blank">' . $tracked_file_node->title . '</a></th>';
  }
  
  // Comment tracking headings.
  foreach ($tracked_commented_nodes as $commented_node) {
    $pane_body .= '<th>' . t('Discussions for') . ':<br/><a href="/' . drupal_get_path_alias('node/' . $commented_node->nid) . '" target="_blank">' . $commented_node->title . '</a></th>';
  }
  
  // Mailchimp metrics headings.
  foreach ($tracked_mailchimp_campaigns as $campaign_title) {
    $pane_body .= '<th>' . t('Email:') . ' ' . $campaign_title . '</th>';
  }
  
  // Survey Gizmo headings.
  foreach ($tracked_surveys as $survey) {
    $pane_body .= '<th>' . t('Survey:') . ' ' . $survey->survey_title . '</th>';
  }
  
  $pane_body .= '</tr></thead><tbody>';
  
  // Prep mailchimp connection.
  $mailchimp_report_controller = NULL;
  if (!empty($tracked_mailchimp_campaigns)) {
    $mailchimp_library_path = libraries_get_path('mailchimp');
    require_once $mailchimp_library_path . '/src/Mailchimp.php';

    $mailchimp_controller = new Mailchimp(variable_get('mailchimp_api_key', 'ebd8449da33ca1d0e49ed026fe8c9876-us1'));
    $mailchimp_report_controller = new Mailchimp_Reports($mailchimp_controller);
  }
  
  // Prep survey gizmo connection.
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  $gizmo_user = variable_get('impetus_panes_sg_email', 'administrator@impetushealthcare.com');
  $gizmo_pass = variable_get('impetus_panes_sg_password', 'impetus3rockz');
  
  for ($i = 0; $i < count($tracked_surveys); $i++) {
    $url = "https://restapi.surveygizmo.com/v4/survey/{$tracked_surveys[$i]->survey_id}/surveyresponse/?user:pass={$gizmo_user}:{$gizmo_pass}&resultsperpage=1";
    curl_setopt($ch, CURLOPT_URL, $url);
    $output = curl_exec($ch);
    $output= json_decode($output);
    
    if ($output->result_ok == TRUE) {
      $total_surveys = $output->total_count;
      $tracked_surveys[$i]->participant_emails = impetus_panes_section_metrics_get_survey_emails($ch, $total_surveys, $gizmo_user, $gizmo_pass, $tracked_surveys[$i]->survey_id);
    } 
  }

  foreach ($users as $loaded_user) {
    $pane_body .= '<tr><td>' . $loaded_user->field_first_name[LANGUAGE_NONE][0]['safe_value'] . '</td><td>' . $loaded_user->field_last_name[LANGUAGE_NONE][0]['safe_value'] . '</td>';
    
    // File Download tracking.
    foreach ($tracked_file_nodes as $nid => $tracked_file_node) {
      if (in_array($nid, array_keys($loaded_user->file_download_nodes))) {
        $pane_body .= '<td><span class="download-status-downloaded">' . t('Downloaded') . '</span></td>';
      }
      else {
        $pane_body .= '<td><span class="download-status-not-downloaded">' . t('Not Downloaded') . '</span></td>';
      }
    }
    
    // Comment tracking.
    foreach ($tracked_commented_nodes as $key => $commented_node) {
      $pane_body .= '<td>' . 
                      t(
                        'Comments for this discussion: <strong>@comment_count</strong>', 
                        array('@comment_count' => isset($loaded_user->comments[$key]) ? count($loaded_user->comments[$key]) : '0')
                      ) . 
                    '</td>';
    }
    
    // Mailchimp campaign tracking.
    if (!empty($tracked_mailchimp_campaigns) && $mailchimp_report_controller != NULL) {
      foreach ($tracked_mailchimp_campaigns as $campaign_id => $campaign_title) {
        
        try {
          $data = $mailchimp_report_controller->memberActivity($campaign_id, array(array('email' => $loaded_user->mail)));
          $opened_status = FALSE;
          $opened_urls = array();
          
          if ($data['error_count'] > 0 && $data['errors'][0]['code'] == 232) {
            $pane_body .= '<td>' . t('Not sent this email') . '</td>';
          }
          else {
            foreach ($data['data'][0]['activity'] as $mc_activity) {
              if ($mc_activity['action'] == 'open') {
                $opened_status = TRUE;
              }
              else if ($mc_activity['action'] == 'click') {
                $opened_urls[] = $mc_activity['url'];
              }
            }
            
            $pane_body .= '<td>';
            
            if ($opened_status) {
              $pane_body .= '<span class="email-opened">' . t('Email Opened') . '</span>';
            }
            else {
              $pane_body .= '<span class="email-not-opened">' . t('Email not Opened') . '</span>';
            }
            
            $pane_body .= '<br/>';
            
            if (!empty($opened_urls)) {
              $pane_body .= '<span class="email-clicked">' . t('Email Links Clicked') . '</span>';
            }
            else {
              $pane_body .= '<span class="email-not-clicked">' . t('Email Links not Clicked') . '</span>';
            }

          }
          
          $pane_body .= '</td>';
        }
        catch (Exception $e) {
          watchdog('Impetus Panes - Metrics Widget', $e->getMessage(), array(), WATCHDOG_ERROR);
        }
      }
    }

    // Survey gizmo metrics.
    if (!empty($tracked_surveys)) {
      
      foreach ($tracked_surveys as $tracked_survey) {
        $pane_body .= '<td>';
        
        if (in_array($loaded_user->mail, $tracked_survey->participant_emails)) {
          $pane_body .= '<span class="survey-submitted">' . t('Survey Submitted') . '</span>';
        }
        else {
          $pane_body .= '<span class="survey-not-submitted">' . t('Survey Not Submitted') . '</span>';
        }
        
        $pane_body .= '</td>';
      }
    }
    
    $pane_body .= '</tr>';
  }
  
  $pane_body .= '</tbody></table>';
  
  return $pane_body;
}

/**
 * Helper function.
 * Gets an array of all emails found within a particular survey's submissions. NOTE these is not necessarily the emails of the
 * participants... however there is no way of figuring out whether or not the email belongs to the participant but this is 
 * HIGHLY unlikely.
 * @param object $ch: A CURL handle.
 * @param int $total_results_number: The amount of respondents for a survey.
 * @param string $gizmo_user: An email address for a survey gizmo user.
 * @param string $gizmo_pass: A password for a survey gizmo user.
 * @param string $survey_id: The survey ID of the survey whose participant emails you want to get.
 * @return array: An array of participant emails.
 */
function impetus_panes_section_metrics_get_survey_emails($ch, $total_results_number, $gizmo_user, $gizmo_pass, $survey_id) {
  
  $api_call_batch_limit = 500;
  $i = 0;
  $survey_email_addresses = array();
  
  do {
    $page = $i + 1;
    $url = "https://restapi.surveygizmo.com/v4/survey/{$survey_id}/surveyresponse/?user:pass={$gizmo_user}:{$gizmo_pass}&page={$page}&resultsperpage={$api_call_batch_limit}";
    curl_setopt($ch, CURLOPT_URL, $url);
    $output = curl_exec($ch);
    $output= json_decode($output);

    foreach ($output->data as $submission) {
      foreach ($submission as $submitted_field) {
        if (filter_var($submitted_field, FILTER_VALIDATE_EMAIL) !== FALSE) {
          $survey_email_addresses[] = $submitted_field;
        }
      }
    }
    
    $i++;
  } while($total_results_number > $api_call_batch_limit * $i);

  return $survey_email_addresses;
}