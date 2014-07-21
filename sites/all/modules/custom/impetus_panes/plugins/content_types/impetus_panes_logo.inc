<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Logo'),
  'description' => t('Simply the logo of the portal.'),
  'category' => t('Impetus'),
  'edit form' => 'impetus_panes_logo_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_logo_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_logo_custom_pane_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 * Notice, the magic that automatically does that for you.
 */
function impetus_panes_logo_custom_pane_edit_form_submit(&$form, &$form_state) {
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function impetus_panes_logo_custom_pane_render($subtype, $conf, $args, $contexts) {

  $image = array(
    'path' => theme_get_setting('logo'),
    'alt' => 'logo',
  );
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = theme('image', $image);

  return $block;
}