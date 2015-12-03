<?php
/**
 * @file
 * add_points_and_badges_view.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function add_points_and_badges_view_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'user_points_and_badges';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'User Points And Badges';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'user_badges_html' => 'user_badges_html',
    'name' => 'name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'user_badges_html' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No results yet!';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: User Badges: Grouped User Badges */
  $handler->display->display_options['fields']['user_badges_html']['id'] = 'user_badges_html';
  $handler->display->display_options['fields']['user_badges_html']['table'] = 'users';
  $handler->display->display_options['fields']['user_badges_html']['field'] = 'user_badges_html';
  $handler->display->display_options['fields']['user_badges_html']['label'] = '';
  $handler->display->display_options['fields']['user_badges_html']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '60';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Userpoints: Current points in category */
  $handler->display->display_options['fields']['points_1']['id'] = 'points_1';
  $handler->display->display_options['fields']['points_1']['table'] = 'userpoints';
  $handler->display->display_options['fields']['points_1']['field'] = 'points';
  $handler->display->display_options['fields']['points_1']['label'] = 'Points';
  $handler->display->display_options['fields']['points_1']['separator'] = '';
  /* Sort criterion: Userpoints: Current points in category */
  $handler->display->display_options['sorts']['points']['id'] = 'points';
  $handler->display->display_options['sorts']['points']['table'] = 'userpoints';
  $handler->display->display_options['sorts']['points']['field'] = 'points';
  $handler->display->display_options['sorts']['points']['order'] = 'DESC';
  /* Contextual filter: User: Group membership (og_user_node) */
  $handler->display->display_options['arguments']['og_user_node_target_id']['id'] = 'og_user_node_target_id';
  $handler->display->display_options['arguments']['og_user_node_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_user_node_target_id']['field'] = 'og_user_node_target_id';
  $handler->display->display_options['arguments']['og_user_node_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['og_user_node_target_id']['break_phrase'] = TRUE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Userpoints total: Current total points */
  $handler->display->display_options['filters']['points']['id'] = 'points';
  $handler->display->display_options['filters']['points']['table'] = 'userpoints_total';
  $handler->display->display_options['filters']['points']['field'] = 'points';
  $handler->display->display_options['filters']['points']['operator'] = '>';
  $handler->display->display_options['filters']['points']['value']['value'] = '0';
  /* Filter criterion: Userpoints: Points category */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'userpoints';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['value'] = array(
    0 => '0',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'points-and-badges';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_2');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Userpoints: Points category */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'userpoints';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: User: Group membership (og_user_node) */
  $handler->display->display_options['arguments']['og_user_node_target_id']['id'] = 'og_user_node_target_id';
  $handler->display->display_options['arguments']['og_user_node_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_user_node_target_id']['field'] = 'og_user_node_target_id';
  $handler->display->display_options['arguments']['og_user_node_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['og_user_node_target_id']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Userpoints total: Current total points */
  $handler->display->display_options['filters']['points']['id'] = 'points';
  $handler->display->display_options['filters']['points']['table'] = 'userpoints_total';
  $handler->display->display_options['filters']['points']['field'] = 'points';
  $handler->display->display_options['filters']['points']['operator'] = '>';
  $handler->display->display_options['filters']['points']['value']['value'] = '0';
  $handler->display->display_options['path'] = 'points-and-badges1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_3');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Userpoints: Points category */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'userpoints';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: User: Group membership (og_user_node) */
  $handler->display->display_options['arguments']['og_user_node_target_id']['id'] = 'og_user_node_target_id';
  $handler->display->display_options['arguments']['og_user_node_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_user_node_target_id']['field'] = 'og_user_node_target_id';
  $handler->display->display_options['arguments']['og_user_node_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_user_node_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['og_user_node_target_id']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Userpoints total: Current total points */
  $handler->display->display_options['filters']['points']['id'] = 'points';
  $handler->display->display_options['filters']['points']['table'] = 'userpoints_total';
  $handler->display->display_options['filters']['points']['field'] = 'points';
  $handler->display->display_options['filters']['points']['operator'] = '>';
  $handler->display->display_options['filters']['points']['value']['value'] = '0';
  $handler->display->display_options['path'] = 'points-and-badges2';
  $export['user_points_and_badges'] = $view;

  return $export;
}
