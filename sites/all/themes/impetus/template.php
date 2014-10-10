<?php

/**
 * @file
 * Theme functions
 */

require_once dirname(__FILE__) . '/includes/structure.inc';
require_once dirname(__FILE__) . '/includes/form.inc';
require_once dirname(__FILE__) . '/includes/menu.inc';
require_once dirname(__FILE__) . '/includes/comment.inc';
require_once dirname(__FILE__) . '/includes/node.inc';

/**
 * Implements theme_preprocess_html.
 */
function impetus_preprocess_html(&$variables) {
  global $user;

  if (in_array('administrator', $user->roles) || in_array('impetus admin', $user->roles) || $user->uid == 1) {
    $variables['classes_array'][] = 'logged-in-admin';
  }
  else if (count($user->roles) == 1 && in_array('authenticated user', $user->roles)) {
    $variables['classes_array'][] = 'regular-user';
  }
}

/**
 * Implements hook_css_alter().
 * Changes the jQuery UI theme to a Bootstrap-like theme
 * from http://addyosmani.github.io/jquery-ui-bootstrap/
 */
function impetus_css_alter(&$css) {
  $radix_path = drupal_get_path('theme', 'radix');

  // Radix now includes compiled stylesheets for demo purposes.
  // We remove these from our subtheme since they are already included
  // in compass_radix.
  unset($css[$radix_path . '/assets/stylesheets/radix-style.css']);
  unset($css[$radix_path . '/assets/stylesheets/radix-print.css']);

  // Add a custom jQuery UI theme.
  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    $css['misc/ui/jquery.ui.theme.css']['data'] =
      drupal_get_path('theme', 'impetus') . '/assets/vendor/jqueryui/jquery-ui-1.10.0.custom.css';
  }
}

/**
 * Implements hook_module_implements_alter().
 * Remove panopoly_core which uses this alter to set it's own jquery_ui theme
 * Should be done in a theme layer, not in panopoly_core
 */
function impetus_module_implements_alter(&$implementations, $hook) {
  if ($hook == 'element_info_alter') {
    unset($implementations['panopoly_core']);
  }
}

/**
 * Implements template_preprocess_page().
 */
function impetus_preprocess_page(&$vars) {
  
  // General pages.
  if (module_exists('chosen')) {
    drupal_add_js(drupal_get_path('theme', 'impetus') . '/assets/javascripts/select-searcher.js');
  }
  
  // Taxonomy pages.
  if (arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
    $term = taxonomy_term_load(arg(2));
    
    // Removing pagers from file taxonomy pages.
    if ($term->vocabulary_machine_name == 'file_categories' && isset($vars['page']['content']['system_main']['pager'])) {
      unset($vars['page']['content']['system_main']['pager']);
    }
  }
  
  // Rework search_form to our liking.
  $vars['search_form'] = '';
  if (module_exists('search') && user_access('search content')) {
    $search_box_form = drupal_get_form('search_form');
    $search_box_form['basic']['keys']['#title'] = '';
    $search_box_form['basic']['keys']['#attributes'] = array('placeholder' => 'Search');
    $search_box_form['basic']['keys']['#attributes']['class'][] = 'search-query';
    $search_box_form['basic']['submit']['#value'] = t('Search');
    $search_box_form['#attributes']['class'][] = 'navbar-form';
    $search_box_form['#attributes']['class'][] = 'pull-right';
    $search_box = drupal_render($search_box_form);
    $vars['search_form'] = (user_access('search content')) ? $search_box : NULL;
  }

  // Add user_badge to header.
  $vars['user_badge'] = '';
  if (module_exists('oa_dashboard')) {
    $user_badge = module_invoke('oa_dashboard', 'block_view', 'oa_user_badge');
    $vars['user_badge'] = $user_badge['content'];
  }
  $toolbar = panels_mini_block_view('oa_toolbar_panel');
  $vars['oa_toolbar_panel'] = isset($toolbar) ? $toolbar['content'] : '';
  $footer = panels_mini_block_view('oa_footer_panel');
  $vars['oa_footer_panel'] = isset($footer) ? $footer['content'] : '';

  ctools_include('content');
  $banner = ctools_content_render('oa_space_banner', '', array(
    'banner_position' => 2
  ));
  if (!empty($banner->content)) {
    $vars['oa_banner'] = $banner->content;
  }
}

/**
 * Implements template_preprocess_fullcalendar.
 */
function impetus_preprocess_fullcalendar(&$variables) {

  if (isset($variables['element']['content']['events']) && property_exists($variables['element']['content']['events'][0]['#entity'], 'field_color_code')) {
    for ($i = 0; $i < count($variables['element']['content']['events']); $i++) {
      for ($j = 0; $j < count($variables['element']['content']['events'][$i]['#event']); $j++) {
        if (!empty($variables['element']['content']['events'][$i]['#entity']->field_color_code['und'])) {
          $variables['element']['content']['events'][$i]['#event'][$j]['#options']['attributes']['color-style'] = $variables['element']['content']['events'][$i]['#entity']->field_color_code['und'][0]['rgb'];
        }
      }
    }
  }
}

/**
 * Implements template_preprocess_node.
 */
function impetus_preprocess_node(&$variables) {
  
  switch ($variables['type']) {
    case 'file':
      
      // Modifying the submitted user's picture.
      $author = user_load($variables['revision_uid']);
      if (property_exists($author, 'picture') && $author->picture != NULL) {
        $variables['user_picture'] = theme(
          'image_style',
          array(
            'style_name' => 'thumbnail',
            'path' => $author->picture->uri,
          )
        );
      }
      else {
        $variables['user_picture'] = '';
      }
      
      // Modifying submitted information.
      $variables['submitted'] = t(
        'Edited by @name on @timestamp', 
        array('@name' => $author->realname, '@timestamp' => date('F d, Y - g:ia', $variables['changed']))
      );
      
      // Modifying the uploaded file field.
      if (isset($variables['content']['field_uploaded_file'])) {
        $variables['content']['field_uploaded_file'][0]['#file']->filename .= ' - ' . t('Click to Download');
      }
      
      // Rendering related files.
      if (isset($variables['content']['field_file_category'])) {
        $query = new EntityFieldQuery();
        $results = $query->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'file')
          ->propertyCondition('status', 1)
          ->fieldCondition('field_file_category', 'tid', $variables['content']['field_file_category'][0]['#options']['entity']->tid)
          ->execute();
        
        if (!empty($results)) {
          $files_in_folder_html = '<div class="files-in-folder">';
          $files_in_folder_html .= '<strong>' . t('Folder Contents') . ':</strong>';
          $files_in_folder_html .= '<ul class="files-in-this-folder-list">';
          $file_nodes = node_load_multiple(array_keys($results['node']));
          
          foreach ($file_nodes as $file_node) {
            $field_items = field_get_items('node', $file_node, 'field_uploaded_file');
            $file_object = (object) $field_items[0];
           
            $files_in_folder_html .= '<li>' .  
              theme_file_link(
                array(
                  'file' => $file_object,
                  'icon_directory' => 'modules/file/icons'
                )
              ) .
              '</li>';
          }
          
          $files_in_folder_html .= '</ul>';
          $files_in_folder_html .= '</div>';
          
          $variables['content']['field_file_category'][0]['#suffix'] = $files_in_folder_html;
        }
      }
      
      // Get version number.
      $variables['content']['version_number'] = array(
        '#prefix' => '<div class="file-version-number">',
        '#suffix' => '</div>',
        '#type' => 'markup',
        '#markup' => '<strong>' . t('Version') . ':</strong><br/>' . t('Version') . ' #' . count(node_revision_list($variables['node'])),
        '#weight' => 50,
      );
      
    break;
    case 'oa_worktracker_task':
      
      if (isset($variables['content']['oa_worktracker_submitted'])) {
        $variables['content']['oa_worktracker_submitted']['#markup'] = '<div class="submitted">' . t('This task was created on @date.', array('@date' => $variables['date'])) . '</div>';
      }
    break;
  }
}

/**
 * Implements theme_form_alter.
 * ...Unfortunately this hook should only be fired in modules instead of themes but there's no other way
 * to alter the "user info" profile form that's generated from open atrium.
 */
function impetus_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'user_profile_form':
      if (module_exists('user_login_alterations') && !user_access('change job title') && isset($form['field_job_title'])) {
        unset($form['field_job_title']);
      }
    break;
  }
}

/**
 * Implements theme_preprocess_privatemsg_view.
 */
function impetus_preprocess_privatemsg_view(&$variables) {
 
  // Changing author's pic.
  if ($variables['message']->author->picture != NULL) {
    $variables['author_picture'] = theme(
      'image_style', 
      array(
        'style_name' => 'thumbnail', 
        'path' => $variables['message']->author->picture->uri,
      )
    );
  }
  else {
    $variables['author_picture'] = '<img src="/' . drupal_get_path('module', 'oa_users') . '/oa-user.png' . '" />';
  }
}

/**
 * Implements theme_preprocess_privatemsg_recipients
 */
function impetus_preprocess_privatemsg_recipients(&$variables) {
  
  global $user;
  $variables['participants'] = t('Conversation between') . ' ';
  $participant_count = count($variables['thread']['participants']);
  $i = 0;
  
  foreach ($variables['thread']['participants'] as $participant) {
    $i++;
    $suffix = '';
    
    if ($i == $participant_count - 1) {
      $suffix = t(' and ');
    }
    else {
      $suffix = ', ';
    }
    
    if ($participant->uid == $user->uid) {
      $variables['participants'] .= t('You') . $suffix;
    }
    else {
      $variables['participants'] .= $participant->realname . $suffix;
    }
  }
  
  $variables['participants'] = substr($variables['participants'], 0, strlen($variables['participants']) - 2);
}

/**
 * Implements template_preprocess_comment.
 */
function impetus_preprocess_comment(&$variables) {
  $loaded_user = user_load($variables['comment']->uid);
 
  if (isset($variables['picture']) && property_exists($loaded_user, 'picture') && $loaded_user->picture != NULL) {
    $user_picture_file = file_load($loaded_user->picture->fid);
    $variables['picture'] = '<div class="user-picture">' .
      theme('image_style', array('style_name' => 'panopoly_image_thumbnail', 'path' => $user_picture_file->uri)) .
      '</div>';
  }
  
  if (isset($variables['submitted'])) {

    if (property_exists($loaded_user, 'realname')) {

      $variables['submitted'] = t(
        'Posted by @name on @date',
        array(
          '@name' => $loaded_user->realname,
          '@date' => date('M d, Y - g:ia', $variables['comment']->created),
        )
      );
    }
  }
}