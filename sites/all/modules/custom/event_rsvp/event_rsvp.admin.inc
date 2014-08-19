<?php
/**
 * @file: Admin forms and functionality.
 */

/**
 * Helper function.
 * Renders the backend RSVP search form.
 */
function event_rsvp_render_admin_form($form, &$form_state) {
  
  $form = array();
  $table_results = '<tr><td>' . t('Sorry, there are no RSVPs yet!') . '<tr><td>';
  
  $form['rsvp_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the event title'),
    '#autocomplete_path' => 'event-rsvp/autocomplete',
    '#size' => 16,
  );
  
  $form['submit'] = array(
    '#prefix' => '<div style="margin-right:10px; display: inline-block;">',
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('Search for RSVPs'),
    '#ajax' => array(
      'callback' => 'event_rsvp_ajax_backend_results',
      'wrapper' => 'table-results',
    ),
  );
  
  $form['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<button onclick="location.reload();" class="form-submit btn">' . t('Reset') . '</button>',
  );
  
  // Calculation of results.
  $results = db_query(
    '
      SELECT n.title, r.realname
      FROM event_rsvp_rsvps e
      INNER JOIN realname r ON e.uid = r.uid
      INNER JOIN node n ON e.nid = n.nid
      LIMIT 0, 100
    '     
  )->fetchAll();
  
  if (!empty($results)) {
    
    $table_results = '';
    
    foreach ($results as $result) {
      $table_results .= '<tr>' .
                          '<td>' . $result->title . '</td>' .
                          '<td>' . $result->realname . '</td>' .
                        '</tr>';
    }
  }
  
  $form['table_results'] = array(
    '#prefix' => '<div style="margin-top: 10px;">',
    '#suffix' => '</div>',
    '#type' => 'markup',
    '#markup' => 
      '<table id="table-results">' .
        '<tr>' .
          '<th>' . t('Event Title') . '</th>' .
          '<th>' . t('RSVPed User') . '</th>' .
        '</tr>' .
        '<tbody>' .
          $table_results .
        '</tbody>' .
      '</table>'
  );
  
  return $form;
}

/**
 * Ajax Handler.
 * Handles searches on the backend RSVP search form.
 */
function event_rsvp_ajax_backend_results($form, $form_state) {
  
  $table_results = '<tr><td>' . t('Sorry, there are no RSVPs for your search.') . '<tr><td>';
  
  // Calculation of results.
  $results = db_query(
    "
      SELECT n.title, r.realname
      FROM event_rsvp_rsvps e
      INNER JOIN realname r ON e.uid = r.uid
      INNER JOIN node n ON e.nid = n.nid
      WHERE n.title = :title
    ",
    array(
      ':title' => $form_state['values']['rsvp_node']
    )
  )->fetchAll();
  
  if (!empty($results)) {
    
    $table_results = '';
    
    foreach ($results as $result) {
      $table_results .= '<tr>' .
                          '<td>' . $result->title . '</td>' .
                          '<td>' . $result->realname . '</td>' .
                        '</tr>';
    }
  }
  
  $form['table_results']['#markup'] = 
    '<table id="table-results">' .
      '<tr>' .
        '<th>' . t('Event Title') . '</th>' .
        '<th>' . t('RSVPed User') . '</th>' .
      '</tr>' .
      '<tbody>' .
        $table_results .
      '</tbody>' .
    '</table>';
  
  return $form['table_results'];
}

/**
 * Menu callback. 
 * Retrieve a JSON object containing autocomplete suggestions for event nodes.
 */
function event_rsvp_node_autocomplete($string = '') {
  $matches = array();
  
  if ($string) {
    $result = db_select('node')
      ->fields('node', array('title'))
      ->condition('type', 'oa_event')
      ->condition('title', db_like($string) . '%', 'LIKE')
      ->range(0, 10)->execute();
    
    foreach ($result as $node) {
      $matches[$node->title] = check_plain($node->title);
    }
  }

  drupal_json_output($matches);
}