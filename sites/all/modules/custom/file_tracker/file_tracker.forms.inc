<?php
/**
 * @file: Functionality of the forms this module uses.
 */

/**
 * Form construction function.
 * Constructs the download tracker form.
 * @return array: A form array.
 */
function file_tracker_download_tracker_form($form, &$form_state) {
  
  $form = array();
  $table_results = '<tr><td>' . t('Sorry, there are no file downloads yet!') . '<tr><td>';
  
  $form['filename'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the file name'),
    '#autocomplete_path' => 'file-tracker/filename-downloads-autocomplete',
    '#size' => 16,
  );
  
  $form['user'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the name of the user'),
    '#autocomplete_path' => 'file-tracker/realname-autocomplete',
    '#size' => 16,
  );
  
  $form['submit'] = array(
    '#prefix' => '<div style="margin-right:10px; display: inline-block;">',
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('Search for File Downloads'),
    '#ajax' => array(
      'callback' => 'file_tracker_ajax_file_downloads_results',
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
      SELECT v.nid, n.title, v.filename, r.realname, v.downloaded_timestamp
      FROM file_tracker_downloads v
      INNER JOIN realname r ON v.uid = r.uid
      INNER JOIN node n ON v.nid = n.nid
      ORDER BY v.downloaded_timestamp DESC
      LIMIT 0, 250
    '     
  )->fetchAll();
  
  if (!empty($results)) {
    
    $table_results = '';
    
    foreach ($results as $result) {
      $table_results .= '<tr>' .
                          '<td><a href="/' . drupal_get_path_alias('node/' . $result->nid) . '">' . $result->title . '</a></td>' .
                          '<td>' . $result->filename . '</td>' .
                          '<td>' . $result->realname . '</td>' .
                          '<td>' . date('d, M Y - g:ia', $result->downloaded_timestamp) . '</td>' .
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
          '<th>' . t('File Title') . '</th>' .
          '<th>' . t('File Name') . '</th>' .
          '<th>' . t('User that Downloaded File') . '</th>' .
          '<th>' . t('Time Downloaded') . '</th>' .
        '</tr>' .
        '<tbody>' .
          $table_results .
        '</tbody>' .
      '</table>'
  );
  
  return $form;
}

/**
 * Form construction function.
 * Constructs the file view tracker form.
 * @return array: A form array.
 */
function file_tracker_view_tracker_form($form, &$form_state) {
  
  $form = array();
  $table_results = '<tr><td>' . t('Sorry, there are no file views yet!') . '<tr><td>';
  
  $form['filename'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the file name'),
    '#autocomplete_path' => 'file-tracker/filename-views-autocomplete',
    '#size' => 16,
  );
  
  $form['user'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the name of the user'),
    '#autocomplete_path' => 'file-tracker/realname-autocomplete',
    '#size' => 16,
  );
  
  $form['submit'] = array(
    '#prefix' => '<div style="margin-right:10px; display: inline-block;">',
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('Search for File Views'),
    '#ajax' => array(
      'callback' => 'file_tracker_ajax_file_views_results',
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
      SELECT v.nid, n.title, v.filename, r.realname, v.viewed_timestamp
      FROM file_tracker_views v
      INNER JOIN realname r ON v.uid = r.uid
      INNER JOIN node n ON v.nid = n.nid
      ORDER BY v.viewed_timestamp DESC
      LIMIT 0, 150
    '     
  )->fetchAll();
  
  if (!empty($results)) {
    
    $table_results = '';
    
    foreach ($results as $result) {
      $table_results .= '<tr>' .
                          '<td><a href="/' . drupal_get_path_alias('node/' . $result->nid) . '">' . $result->title . '</a></td>' .
                          '<td>' . $result->filename . '</td>' .
                          '<td>' . $result->realname . '</td>' .
                          '<td>' . date('d, M Y - g:ia', $result->viewed_timestamp) . '</td>' .
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
          '<th>' . t('File Title') . '</th>' .
          '<th>' . t('File Name') . '</th>' .
          '<th>' . t('User that Viewed File') . '</th>' .
          '<th>' . t('Time Viewed') . '</th>' .
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
 * Handles searches on the backend file views tracker form.
 */
function file_tracker_ajax_file_views_results($form, $form_state) {
  
  $table_results = '<tr><td>' . t('Sorry, there are no file views for your search.') . '<tr><td>';
  
  // Calculation of results.
  $query = db_select('file_tracker_views', 'v');

  $query->join('realname', 'r', 'v.uid = r.uid');
  $query->join('node', 'n', 'v.nid = n.nid');
  
  $query->fields('n', array('title'))
    ->fields('r', array('realname'))
    ->fields('v', array('nid', 'filename', 'viewed_timestamp'))
    ->orderBy('v.viewed_timestamp', 'DESC')
    ->range(0, 250);
  
  if ($form_state['values']['filename'] != '') {
    $query->condition('v.filename', $form_state['values']['filename'], '=');
  }
  
  if ($form_state['values']['user'] != '') {
    $query->condition('r.realname', $form_state['values']['user'], '=');
  }
  
  $executed_query = $query->execute();
  $results = $executed_query->fetchAll();
  
  
  if (!empty($results)) {
    
    $table_results = '';
    
    foreach ($results as $result) {
      $table_results .= '<tr>' .
                          '<td><a target="_blank" href="/' . drupal_get_path_alias('node/' . $result->nid) . '">' . $result->title . '</a></td>' .
                          '<td>' . $result->filename . '</td>' .
                          '<td>' . $result->realname . '</td>' .
                          '<td>' . date('d, M Y - g:ia', $result->viewed_timestamp) . '</td>' .
                        '</tr>';
    }
  }
  
  $form['table_results']['#markup'] = 
    '<table id="table-results">' .
      '<tr>' .
        '<th>' . t('File Title') . '</th>' .
        '<th>' . t('File Name') . '</th>' .
        '<th>' . t('User that Viewed File') . '</th>' .
        '<th>' . t('Time Viewed') . '</th>' .
      '</tr>' .
      '<tbody>' .
        $table_results .
      '</tbody>' .
    '</table>';
  
  return $form['table_results'];
}

/**
 * Ajax Handler.
 * Handles searches on the backend file views tracker form.
 */
function file_tracker_ajax_file_downloads_results($form, $form_state) {
  
  $table_results = '<tr><td>' . t('Sorry, there are no file downloads for your search.') . '<tr><td>';
  
  // Calculation of results.
  $query = db_select('file_tracker_downloads', 'v');

  $query->join('realname', 'r', 'v.uid = r.uid');
  $query->join('node', 'n', 'v.nid = n.nid');
  
  $query->fields('n', array('title'))
    ->fields('r', array('realname'))
    ->fields('v', array('nid', 'filename', 'downloaded_timestamp'))
    ->orderBy('v.downloaded_timestamp', 'DESC')
    ->range(0, 250);
  
  if ($form_state['values']['filename'] != '') {
    $query->condition('v.filename', $form_state['values']['filename'], '=');
  }
  
  if ($form_state['values']['user'] != '') {
    $query->condition('r.realname', $form_state['values']['user'], '=');
  }
  
  $executed_query = $query->execute();
  $results = $executed_query->fetchAll();
  
  
  if (!empty($results)) {
    
    $table_results = '';
    
    foreach ($results as $result) {
      $table_results .= '<tr>' .
                          '<td><a target="_blank" href="/' . drupal_get_path_alias('node/' . $result->nid) . '">' . $result->title . '</a></td>' .
                          '<td>' . $result->filename . '</td>' .
                          '<td>' . $result->realname . '</td>' .
                          '<td>' . date('d, M Y - g:ia', $result->viewed_timestamp) . '</td>' .
                        '</tr>';
    }
  }
  
  $form['table_results']['#markup'] = 
    '<table id="table-results">' .
      '<tr>' .
        '<th>' . t('File Title') . '</th>' .
        '<th>' . t('File Name') . '</th>' .
        '<th>' . t('User that Viewed File') . '</th>' .
        '<th>' . t('Time Viewed') . '</th>' .
      '</tr>' .
      '<tbody>' .
        $table_results .
      '</tbody>' .
    '</table>';
  
  return $form['table_results'];
}

/**
 * Menu callback. 
 * Retrieve a JSON object containing autocomplete suggestions for file names when on the file views page.
 */
function file_tracker_filename_views_autocomplete($string = '') {
  $matches = array();
  
  if ($string) {
    $result = db_select('file_tracker_views')
      ->fields('file_tracker_views', array('filename'))
      ->condition('filename', db_like($string) . '%', 'LIKE')
      ->range(0, 10)->execute();
    
    foreach ($result as $filename) {
      $matches[$filename->filename] = check_plain($filename->filename);
    }
  }

  drupal_json_output($matches);
}

/**
 * Menu callback. 
 * Retrieve a JSON object containing autocomplete suggestions for file names when on the file downloads page.
 */
function file_tracker_filename_downloads_autocomplete($string = '') {
  $matches = array();
  
  if ($string) {
    $result = db_select('file_tracker_downloads')
      ->fields('file_tracker_downloads', array('filename'))
      ->condition('filename', db_like($string) . '%', 'LIKE')
      ->range(0, 10)->execute();
    
    foreach ($result as $filename) {
      $matches[$filename->filename] = check_plain($filename->filename);
    }
  }

  drupal_json_output($matches);
}

/**
 * Menu callback. 
 * Retrieve a JSON object containing autocomplete suggestions for user's real names.
 */
function file_tracker_realname_autocomplete($string = '') {
  $matches = array();
  
  if ($string) {
    $result = db_select('realname')
      ->fields('realname', array('realname'))
      ->condition('realname', db_like($string) . '%', 'LIKE')
      ->range(0, 10)->execute();
    
    foreach ($result as $realname) {
      $matches[$realname->realname] = check_plain($realname->realname);
    }
  }

  drupal_json_output($matches);
}