<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Section menu'),
  'description' => t('Widget containing the section menu'),
  'category' => t('Widgets'),
  'render callback' => 'change_section_destination_menu_render',
  'all contexts' => TRUE,
);

function change_section_destination_menu_render($subtype, $conf, $args, $contexts) {
  $block = new stdClass();
  $sections = db_select('node' , 'n')
    ->fields('n' , array('nid' , 'title'))
    ->condition('type' , 'oa_space' , '=')
    ->execute();
  while($section = $sections->fetchAssoc()) {
  	$node = node_load($section['nid']);
  	if (isset($node->field_display_in_top_menu[LANGUAGE_NONE][0]['value']) && $node->field_display_in_top_menu[LANGUAGE_NONE][0]['value'] == 1) {
  	  $allowed_nodes[] = array('nid' => $node->nid , 'title' => $node->title);
  	}
  }
  if (!empty($allowed_nodes)) {
  	$menu = '<div class="widget-menu">';
  	$menu .= '<ul class="menu">';
  	foreach ($allowed_nodes as $node){
  	  $menu .= '<li class="menu-item">' . l($node['title'] , 'node/' . $node['nid']) . '</li>';
  	}
  	$menu .= '</ul>';
  	$menu .= '</div>';
  }
  $block->subject = t('Wdiget space menu');
  $block->content = $menu;

  return $block;
}

?>