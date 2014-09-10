<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Profile Form'),
  'description' => t('A profile form that will allow people to edit some fields.'),
  'category' => t('User Content'),
  'edit form' => 'impetus_panes_profile_form_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_profile_form_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_profile_form_custom_pane_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function impetus_panes_profile_form_custom_pane_edit_form_submit(&$form, &$form_state) {
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info.
 */
function impetus_panes_profile_form_custom_pane_render($subtype, $conf, $args, $contexts) {
    
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  if (arg(0) == 'user' && is_numeric(arg(1))) {
    
    global $user;
    $user_page_user = user_load(arg(1));
    
    if (
      $user_page_user !== FALSE && 
      (
        $user->uid == $user_page_user->uid || 
        $user->uid == 1 ||
        (property_exists($user, 'roles') && in_array('administrator', $user->roles) || in_array('impetus admin', $user->roles))
      )
    ) {
      
      $form_state['build_info']['args'] = array($user_page_user, 'user-info');
      form_load_include($form_state, 'inc', 'user', 'user.pages');
      $user_form = drupal_build_form('user_profile_form', $form_state);
      
      if (isset($user_form['field_first_name'])) {
        unset($user_form['field_first_name']);
      }
      if (isset($user_form['field_last_name'])) {
        unset($user_form['field_last_name']);
      }
      if (isset($user_form['field_user_picture']) && isset($user_form['field_user_picture']['und'][0]['alt'])) {
        unset($user_form['field_user_picture']['und'][0]['alt']);
      }
      
      $block->content = render($user_form);
    }
    
  }
  
  return $block;
}
