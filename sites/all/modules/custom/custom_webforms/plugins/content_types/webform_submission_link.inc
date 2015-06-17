<?php

// Plugin definition
$plugin = array(
  'single' => TRUE,
  'title' => t('Add edit link'),
  'description' => t('Adds a widget containing a link where you can view your submissions'),
  'category' => t('Impetus'),
  'render callback' => 'widget_submissions',
  'all contexts' => TRUE,
);

function widget_submissions($subtype, $conf, $args, $contexts) {
  $nid = arg(1);

  $block = new stdClass();
  $block->content = l(t("Go to list of your submissions"), 'webform/' . $nid . '/submissions');
  
  return $block;
}