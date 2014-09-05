<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Survey Gizmo'),
  'description' => t('Safely embeds survey gizmo javascript code.'),
  'category' => t('Impetus'),
  'edit form' => 'impetus_panes_survey_gizmo_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_survey_gizmo_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_survey_gizmo_custom_pane_edit_form($form, &$form_state) {
  
  $form['embed_code'] = array(
    '#type' => 'textarea',
    '#title' => t('Survey Gizmo Javascript Embed Code'),
    '#description' => t('DO NOT modify the Survey Gizmo embed code OR put anything else in this box. Doing so will break the page.') .
                      '<br/><strong>' . t('Refresh the page after you save this widget in order to see the survey') . '</strong>',
    '#required' => TRUE,
    '#default_value' => $form_state['conf']['embed_code'],
  );
  
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function impetus_panes_survey_gizmo_custom_pane_edit_form_submit(&$form, &$form_state) {
  
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
function impetus_panes_survey_gizmo_custom_pane_render($subtype, $conf, $args, $contexts) {
  
  // Set up some javascript and variables.
  global $user;
  $loaded_user = user_load($user->uid);
  $first_name = field_get_items('user', $loaded_user, 'field_first_name');
  $last_name = field_get_items('user', $loaded_user, 'field_last_name');
  
  if ($first_name != FALSE && $last_name != FALSE) {
    drupal_add_js(
      array(
        'impetusPanes' => array(
          'firstName' => $first_name[0]['safe_value'],
          'lastName' => $last_name[0]['safe_value'],
          'email' => $loaded_user->mail,
        )
      ),
      'setting'
    );
    drupal_add_js(drupal_get_path('module', 'impetus_panes') . '/js/impetus_panes_survey_gizmo.js');
  }
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  if (isset($conf['embed_code']) && $conf['embed_code'] != '') {
    $html = $conf['embed_code'];

    // Extract the proper script tag from survey gizmo's javascript embed.
    $protocol = (stripos($_SERVER['SERVER_PROTOCOL'], 'https') === true) ? 'https://' : 'http://';
    $script_src =  $protocol . substr($html , strpos($html , 'www.surveygizmo.com'));
    $script_src =  substr($script_src, 0 , strpos($script_src , 'ref=') + 4) . $protocol . filter_input(INPUT_SERVER, 'HTTP_HOST', FILTER_SANITIZE_STRING) . '/' . drupal_lookup_path('alias', current_path());
    $script_tag = '<script type="text/javascript" src="' . $script_src . '"></script>';

    // Extract the proper noscript html from survey gizmo's javascript embed.
    libxml_use_internal_errors(TRUE);
    $dom = new DOMDocument();
    $dom->loadHTML($html);
    $noscript_tag = '<noscript id="gizmo-noscript">' .
                      '<a href="' . $dom->getElementsByTagName('a')->item(1)->getAttribute('href') . '">' . $dom->getElementsByTagName('a')->item(1)->nodeValue . '</a>' .
                    '</noscript>';

    // Add the proper survey gizmo html to the panel.
    $block->content = $script_tag . $noscript_tag;
  }
  
  return $block;
}
