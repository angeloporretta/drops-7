<?php
/**
 * @file
 * Theme and preprocess functions for menus
 */

/**
 * Implements theme_menu_tree().
 */
function impetus_menu_tree(&$variables) {
  // override Radix menu.inc with default Drupal behavior
  return theme_menu_tree($variables);
}

/**
 * Implements theme_menu_link().
 */
function impetus_menu_link(&$variables) {
  // override Radix menu.inc with default Drupal behavior
  if (isset($variables['element']['#original_link']['menu_name']) && $variables['element']['#original_link']['menu_name'] == 'og-menu-single') {
	$element = $variables['element'];
  	$sub_menu = '';

  	if ($element['#below']) {
      $sub_menu = drupal_render($element['#below']);
  	}
  	$split = explode('/' , $variables['element']['#href']);
  	if ($split[0] == 'node' && is_numeric($split[1])) {
  	  $node = node_load($split[1]);
  	  if (isset($node->field_dummy_content[LANGUAGE_NONE][0]['value']) && $node->field_dummy_content[LANGUAGE_NONE][0]['value'] == 1) {
  	  	$output = l($element['#title'], NULL , array('fragment' => TRUE , 'external' => TRUE , 'attributes' => array('class' => array('dummy-link'))));
  	  } else {
  	  	$output = l($element['#title'], $element['#href'], $element['#localized_options']);
  	  }
  	} else {
  	  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  	}
  	return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
  }
  return theme_menu_link($variables);
}

/**
 * Implements theme_menu_tree__MENU_NAME().
 */
function impetus_menu_tree__oa_navigation(&$variables) {
  return '<ul class="menu nav">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_link__MENU_NAME().
 */
function impetus_menu_link__oa_navigation(&$variables) {
  return radix_menu_link($variables);
}
