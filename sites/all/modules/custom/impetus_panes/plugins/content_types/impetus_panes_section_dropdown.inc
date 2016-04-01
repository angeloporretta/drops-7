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
  $inside = array();
  $block = new stdClass();
  $block->title = ''; 
  $block->content = '';
  $flag = flag_get_flag('remove_from_top_nav');

  $menu_items_id = db_select('node' , 'n')
    ->fields('n')
    ->condition('type' , 'oa_space' , '=')
    ->execute();

  while ($menu_item = $menu_items_id->fetchAssoc()) {
    $menu = db_select('menu_links' , 'm')
      ->fields('m' , array('link_title' , 'mlid' , 'weight'))
      ->condition('menu_name' , 'og-menu-single' , '=')
      ->condition('plid' , 0 ,'=')
      ->condition('hidden', 0)
      ->condition('link_path' , 'node/' . $menu_item['nid']);
    $result = $menu->execute();
    while ($men = $result->fetchAssoc()) {
      $men['nid'] = $menu_item['nid'];
      $og_menu[] = $men;
    }
  }
  if (!empty($og_menu))
  usort($og_menu , "compare_weight_callback");

  // $menu = db_select('menu_links' , 'm');
  // $menu->join('node' , 'n' , 'n.title = m.link_title');
  // $menu->groupBy('m.link_title');
  // $menu->fields('m' , array('link_title' , 'mlid' , 'weight'))
  //   ->condition('menu_name' , 'og-menu-single' , '=')
  //   ->condition('plid' , '0' ,'=');
  // $menu->fields('n' , array('nid'))
  //   ->condition('type' , 'oa_space' , '=');
  // $menu->condition('n.nid' )
  // $menu->orderBy('m.weight' , 'ASC');
  // $result = $menu->execute();
  // while ($men = $result->fetchAssoc()) {
  //   dsm($men);
  //   $og_menu[] = $men;
  // }
  $i = 0;
  if (!empty($og_menu)) {
  $allowed_space_nodes = $og_menu;
  foreach($allowed_space_nodes as $nodes) {
    $node = node_load($nodes['nid']);
    $node_menu_setting = _get_menu_links_settings($node->nid);
    if (isset($node_menu_setting['enabled']) && empty($node_menu_setting['enabled'])) {
      unset($allowed_space_nodes[$i]);
    }
    if (node_access('view' , $node) == FALSE) {
      unset($allowed_space_nodes[$i]);
    }
    if (isset($node->field_display_in_top_menu[LANGUAGE_NONE][0]['value'])){
      if ($node->field_display_in_top_menu[LANGUAGE_NONE][0]['value'] == 1) {
        unset($allowed_space_nodes[$i]);
        if (node_access('view' , $node) == TRUE)
        $inside[] = array('nid' => $node->nid , 'title' => $node->title);
      }
    }
    $i++;
  }

    // Get the sections under the allowed spaces.
  if (!empty($allowed_space_nodes)) {
    //sort the spaces based on the og menu
    foreach ($allowed_space_nodes as $i => $value) {
        $allowed_space_nodes[$i] = (object)$allowed_space_nodes[$i];
        $submenu_items = impetus_panes_submenu_tree_all_data('og-menu-single', $allowed_space_nodes[$i]->mlid);
        $allowed_space_nodes[$i]->section_nodes = array();
        usort($submenu_items , "compare_weight_callback");
        // $submenu_items = _sort_by_weight($submenu_items);
        if (!empty($submenu_items)) {
          foreach ($submenu_items as $submenu_item) {
            $section_node = menu_get_object('node', 1, $submenu_item['link_path']);
            if ($section_node != '' && node_access('view', $section_node) && $flag->is_flagged($section_node->nid) == "") {
              $allowed_space_nodes[$i]->section_nodes[] = $section_node;
            }
          }
        }
    }
  }

  if (arg(0) == 'node' && is_numeric(arg(1)) && arg(2) == '') {
    $current_node = node_load(arg(1));
  }
     $items_per_column = variable_get('column_items', '');
     $number_of_columns = ceil(sizeof($inside) / $items_per_column);
     // Create html structure.
     $block->content .= '<ul class="spaces-section-dropdown">';

    foreach ($allowed_space_nodes as $space_node) {
      $class = '';
      if (isset($current_node) && $current_node->nid == $space_node->nid) {
        $class = ' active';
      }
      if (property_exists($space_node, 'section_nodes')) {
        $number_of_columns = ceil(count($space_node->section_nodes) / $items_per_column);
        if ($number_of_columns > 0) {
          $width = 100/$number_of_columns;
        } else {
          $width = 100;
        }
        if (isset($current_node) && $current_node === $space_node) {
          $class = ' active';
        }
        if(isset($current_node->og_group_ref) && $current_node->og_group_ref[LANGUAGE_NONE][0]['target_id'] == $space_node->nid) {
          $class = ' active';
        }
        if (isset($current_node)) {
          foreach ($space_node->section_nodes as $node) {
            if ($node === $current_node) {
              $class = ' active';
            }
          }
        }
        $block->content .= '<li class="dropdown' . $class . '"><a href="/' . drupal_get_path_alias('node/' . $space_node->nid) . '"' . '>' . $space_node->link_title . '</a>';
        if (!empty($space_node->section_nodes)) {
          $block->content .= '<ul class="nested hide" style="width:' . 200*$number_of_columns . 'px">';
          $block->content .= '<li class="close-button"><button>X</button></li>';
          $this_column_items = 0;
          foreach ($space_node->section_nodes as $section_node) {
            if($this_column_items == 0) {
              $block->content .= '<div class="menu-column" style="width:' . $width . '%">';
            }
            $block->content .= '<li><a href="/' . drupal_get_path_alias('node/' . $section_node->nid) . '">' . $section_node->title . '</a></li>';
            $this_column_items++;
            if ($this_column_items == $items_per_column) {
              $this_column_items = 0;
              $block->content .= "</div>";
            }
          }
          $block->content .= '</ul>';
        }
        $block->content .= '</li>';
      }
      else {
        $block->content .= '<li><a href="/' . drupal_get_path_alias('node/' . $space_node->nid) . '">' . $space_node->link_title . '</a></li>';
      }
    }
    $block->content .= '</ul>';
  }
  return $block;
}

/**
 * Helper Function.
 * Gets the 2nd level children (the one below root) of a menu.
 * @param string $menu_name: The name of the menu whose children you want, for example "footer-menu".
 * @param string $link_path: The link path of the parent item whose children you want, for example "node/43".
 * @return array: An array structure of the child menu item or an empty array if the parent item has no children.
 */
function impetus_panes_submenu_tree_all_data($menu_name, $plid) {
  $return = array();
  $childrens = db_select('menu_links' , 'm')
    ->fields('m' , array('link_title' , 'link_path', 'weight'))
    ->condition('menu_name' , $menu_name , '=')
    ->condition('plid' , $plid , '=')
    ->execute();

  while($children = $childrens->fetchAssoc()) {
    $return[] = $children;
  }

  return $return;
}

function compare_weight_callback($a , $b) {
  if ($a['weight'] > $b['weight']) {
    return 1;
  } else {
    return -1;
  }
}