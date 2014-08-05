<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Section Dropdown'),
  'description' => t('Lists the spaces someone belongs to and drops down their sections.'),
  'category' => t('Impetus'),
  'edit form' => 'impetus_panes_section_dropdown_custom_pane_edit_form', 
  'render callback' => 'impetus_panes_section_dropdown_custom_pane_render',
  'all contexts' => TRUE,
);

/**
 * An edit form for the pane's settings.
 */
function impetus_panes_section_dropdown_custom_pane_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Submit function, note anything in the formstate[conf] automatically gets saved
 */
function impetus_panes_section_dropdown_custom_pane_edit_form_submit(&$form, &$form_state) {
} 

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info.
 */
function impetus_panes_section_dropdown_custom_pane_render($subtype, $conf, $args, $contexts) {
  
  // Adding resources.
  drupal_add_css(drupal_get_path('module', 'impetus_panes') . '/css/impetus_panes_section_dropdown.css');
  drupal_add_js(drupal_get_path('module', 'impetus_panes') . '/js/impetus_panes_section_dropdown.js');
  
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  
  if (!impetus_panes_is_admin()) {
    // Get the spaces this user has access to.
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'oa_space')
      ->propertyCondition('status', 1)
      ->execute();

    $space_nodes = node_load_multiple(array_keys($result['node']));
    $allowed_space_nodes = array();

    foreach ($space_nodes as $nid => $space_node) {
      if (node_access('view', $space_node) == TRUE) {
        $allowed_space_nodes[] = $space_node;
      }
    }

    // Get the sections under the allowed spaces.
    if (!empty($allowed_space_nodes)) {

      for ($i = 0; $i < count($allowed_space_nodes); $i++) {
        $query = new EntityFieldQuery();
        $result = $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'oa_section')
          ->propertyCondition('status', 1)
          ->fieldCondition('og_group_ref', 'target_id', array($allowed_space_nodes[$i]->nid), 'IN')
          ->execute();

        if (!empty($result)) {
          $section_nodes = node_load_multiple(array_keys($result['node']));
          foreach ($section_nodes as $nid => $section_node) {
            if (node_access('view', $section_node) == TRUE) {
              $allowed_space_nodes[$i]->section_nodes[$nid] = $section_node;
            }
          }
        }
      }
    }

    // Create html structure.
    $block->content .= '<ul class="spaces-section-dropdown">';
    foreach ($allowed_space_nodes as $space_node) {

      if (property_exists($space_node, 'section_nodes')) {
        $block->content .= '<li class="dropdown"><a href="/' . drupal_get_path_alias('node/' . $space_node->nid) . '">' . $space_node->title . '</a><ul class="nested hide">';
        foreach ($space_node->section_nodes as $section_node) {
          $block->content .= '<li><a href="/' . drupal_get_path_alias('node/' . $section_node->nid) . '">' . $section_node->title . '</a></li>';
        }
        $block->content .= '</ul></li>';
      }
      else {
        $block->content .= '<li><a href="/' . drupal_get_path_alias('node/' . $space_node->nid) . '">' . $space_node->title . '</a></li>';
      }
    }

    $block->content .= '</ul>';
  }
  
  return $block;
}