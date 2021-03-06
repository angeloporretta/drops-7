<?php
/**
 * @file: All functionality for forms created by this module.
 */

/**
 * Helper function.
 * Renders the add bulk files form. Will return an empty array if the user does not have permission to use the form.
 */
function bulk_file_upload_add_files_form($form, &$form_state, $tid) {
  global $user;
  $form = array();
  
  

  if (user_access('access bulk upload page')) {
    
    drupal_add_css(drupal_get_path('module', 'bulk_file_upload') . '/css/bulk_file_upload_upload_page.css');
    drupal_add_js(drupal_get_path('module', 'bulk_file_upload') . '/js/bulk_file_upload_upload_page.js');
    
    $form['new_upload_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Click to Add New Files'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['new_upload_fields']['files'] = array(
      '#prefix' => '<div id="files-wrapper">',
      '#suffix' => '</div>',
      '#type' => 'fieldset',
      '#title' => t('Files you want to upload'),
    );
    
    $form['new_upload_fields']['tid'] = array(
      '#type' => 'hidden',
      '#value' => $tid,
    );


    

    $folder = taxonomy_term_load($tid);
    $form['new_upload_fields']['folder_prompt'] = array(
      '#type' => 'markup',
      '#markup' => t(
        'You will be uploading these files into the <strong>@folder_name</strong> folder.',
        array('@folder_name' => $folder->name)
      ),
      '#weight' => -49,
    );


    // if (in_array('impetus admin', $user->roles) || in_array('administrator', $user->roles) || $user->uid == 1) {
      
    //   $space_options = array();
    //   $section_options = array();
      
    //   $space_query = new EntityFieldQuery();
    //   $space_results = $space_query->entityCondition('entity_type', 'node')
    //     ->entityCondition('bundle', 'oa_space')
    //     ->propertyCondition('status', 1)
    //     ->propertyOrderBy('title', 'ASC')
    //     ->execute();
      
    //   if (!empty($space_results)) {
    //     $space_nodes = node_load_multiple(array_keys($space_results['node']));
        
    //     foreach ($space_nodes as $space_node) {
    //       $space_options[$space_node->nid] = $space_node->title;
    //     }
    //   }
      
      // $form['new_upload_fields']['space'] = array(
      //   '#type' => 'select',
      //   '#title' => t('Space'),
      //   '#required' => TRUE,
      //   '#options' => $space_options,
      //   '#default_value' => '',
      //   '#empty_option' => '- ' . t('None') . ' -',
      //   '#weight' => -48,
      //   '#ajax' => array(
      //     'callback' => 'bulk_file_upload_ajax_sections',
      //     'wrapper' => 'section-field-wrapper',
      //   ),
      // );
      
      // if (isset($_SESSION['oa_space_id'])) {
      //   $section_query = new EntityFieldQuery();
      //   $section_results = $section_query->entityCondition('entity_type', 'node')
      //     ->entityCondition('bundle', 'oa_section')
      //     ->propertyCondition('status', 1)
      //     ->fieldCondition('og_group_ref', 'target_id', $_SESSION['oa_space_id'])
      //     ->propertyOrderBy('title', 'ASC')
      //     ->execute();
        
      //   if (!empty($section_results)) {
      //     $section_nodes = node_load_multiple(array_keys($section_results['node']));
        
      //     foreach ($section_nodes as $section_node) {
      //       $section_options[$section_node->nid] = $section_node->title;
      //     }
      //   }
      // }
      
      // $form['new_upload_fields']['section'] = array(
      //   '#type' => 'select',
      //   '#prefix' => '<div id="section-field-wrapper">',
      //   '#suffix' => '</div>',
      //   '#title' => t('Section'),
      //   '#required' => TRUE,
      //   '#options' => $section_options,
      //   '#default_value' => '',
      //   '#empty_option' => '- ' . t('None') . ' -',
      //   '#weight' => -47,
      //   '#validated' => TRUE,
      // );
   // }

    // $form['new_upload_fields']['file'] = array(
    //     '#type' => 'file',
    //     '#name' => 'files[]',
    //     '#title' => t('Choose some files'),
    //     //'#description' => t('JPG\'s, GIF\'s, and PNG\'s only, 10MB Max Size'),
    //     '#attributes' => array('multiple' => 'multiple'),
    // );

    // $form['new_upload_fields']['dnd'] = array(
    // '#tree' => TRUE,
    // '#type' => 'dragndrop_upload',
    // '#title' => t('Drag & Drop files here'),
    // '#file_upload_max_size' => '100M',
    // '#upload_location' => 'public://',
    // '#upload_event' => 'manual',
    // '#multiupload' => TRUE,
    // '#cardinality' => -1,


    //'#value_callback' => 'dragndrop_upload_multi_widget_value',
    // '#theme' => 'file_widget_multiple',
    // '#display_field ' => 0,
    //);

    $field = field_info_field('field_drag_and_drop_upload');
    $instance = field_info_instance('node', 'field_drag_and_drop_upload', 'file');
    @$my_field = field_default_form('node', NULL, $field, $instance, LANGUAGE_NONE, array(), $form, $form_state);
    $my_field['field_drag_and_drop_upload'][LANGUAGE_NONE]['#file_upload_description'] .= "<br />In order to upload files larger than <strong>100 MB</strong> " . l(t("Click here") , 'node/add/file');
    $form['new_upload_fields']['dnd'] = $my_field['field_drag_and_drop_upload'];
    $form['new_upload_fields']['dnd']['#weight'] = -40;
    //$form['new_upload_fields']['field_set'] = field_create_instance($dnd);

    // for ($i = 0; $i < 1; $i++) {
    //   $form['new_upload_fields']['files']['file_upload_' . $i] = array(
    //     '#type' => 'managed_file',
    //     '#title' => t('Choose a file'),
    //     '#attributes' => array('multiple' => 'multiple'),
    //     '#upload_location' => 'private://' . $node_upload_field_info['settings']['file_directory'] . '/',
    //     '#upload_validators' => array(
    //       'file_validate_extensions' => array($node_upload_field_info['settings']['file_extensions']),
    //     ),
    //   );
    // }

    // $form['new_upload_fields']['add_more'] = array(
    //   '#type' => 'button',
    //   '#value' => t('Add More'),
    // );

    $form['new_upload_fields']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Upload Files'),
    );

    // $form['new_upload_fields']['submit_1'] = array(
    //   '#type' => 'submit',
    //   '#value' => t('Upload files with drag and drop'),
    // );

    $form['#validate'] = array('bulk_file_upload_add_files_form_validate');
    $form['#submit'] = array('bulk_file_upload_add_files_form_submit');
  }

  return $form;
  
}

/**
 * Ajax Callback.
 * Populates the section field based on the space field for the bulk add files form.
 */
function bulk_file_upload_ajax_sections($form, &$form_state) {

  global $user;
  
  if (in_array('impetus admin', $user->roles) || in_array('administrator', $user->roles) || $user->uid == 1) {
    
    $section_options = array('' => '- ' . t('None') . ' -');
    
    if ($form_state['values']['space'] != '') {
      $section_query = new EntityFieldQuery();
      $section_results = $section_query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'oa_section')
        ->propertyCondition('status', 1)
        ->fieldCondition('og_group_ref', 'target_id', $form_state['values']['space'])
        ->propertyOrderBy('title', 'ASC')
        ->execute();

      if (!empty($section_results)) {
        $section_nodes = node_load_multiple(array_keys($section_results['node']));

        foreach ($section_nodes as $section_node) {
          $section_options[$section_node->nid] = $section_node->title;
        }
      }
    }
    
    $form['new_upload_fields']['section']['#options'] = $section_options;
    return $form['new_upload_fields']['section'];
  }
}

/**
 * Validation handler.
 * Handles the validation for the bulk add files form.
 */
function bulk_file_upload_add_files_form_validate($form, &$form_state) {

  $term = taxonomy_term_load($form_state['values']['tid']);
  if ($term == FALSE || $term->vocabulary_machine_name != 'file_categories') {
    form_set_error('files', t('Error: You are trying to save these files under a restricted folder.'));
  }
  // $num_files = count($_FILES['files']['name']);
  //   for ($i = 0; $i < $num_files; $i++) {
  //     $validators = array('file_validate_extensions' => array('roq , mxf , asf , yuv , avi , mng , drc , ogv , ogg , mkv , webm , flv , qt , rm , wmv , mp4 , m4p , m4v , mpg , mp2 , mp3 , mpeg , mpe , rmvb , svi , 3gp , 3g2 , mpv , nsv , mov , docx , xslx , pptx , jpg , jpeg , gif , png , txt , doc , xls , pdf , ppt , pps , odt , ods , odp'));
  //       $file = file_save_upload($i, $validators);
  //       if ($file) {
  //           if ($file = file_move($file, 'public://')) {
  //               $form_state['values']['file'][$i] = $file;
  //           }
  //           else {
  //               form_set_error('file', t('Failed to write the uploaded file the site\'s file folder.'));
  //           }
  //       }
  //       else {
  //           form_set_error('file', t('No file was uploaded.'));
  //       }   
  //   }
}

/**
 * Submission handler.
 * Handles the submission for the bulk add files form.
 */
function bulk_file_upload_add_files_form_submit($form, &$form_state) {

  global $user;
  global $language;

  $new_file_node = (object) NULL;
  $new_file_node->type = 'file';
  $new_file_node->language = $language->language;
  $new_file_node->uid = $user->uid;
  $new_file_node->created = strtotime('now');
  $new_file_node->changed = strtotime('now');
  $new_file_node->status = 1;
  $new_file_node->comment = 2;
  $new_file_node->promote = 0;
  $new_file_node->moderate = 0;
  $new_file_node->sticky = 0;
  $new_file_node->validated = TRUE;
  $new_file_node->is_new = TRUE;
  $new_file_node->timestamp = strtotime('now');
  
  if (isset($form_state['values']['tid']) && ctype_digit($form_state['values']['tid'])) {
    $new_file_node->field_file_category['und'][0]['tid'] = $form_state['values']['tid'];
  }

  foreach ($form_state['values']['dnd'][LANGUAGE_NONE] as $element) {
      // if (isset($form_state['values']['space']) && isset($form_state['values']['section'])) {
      //   // $new_file_node->og_group_ref['und'][0]['target_id'] = $form_state['values']['space'];
      //   // $new_file_node->og_group_ref['und'][0]['field_mode'] = 'default';
      //   // $new_file_node->oa_section_ref['und'][0]['target_id'] = $form_state['values']['section'];
      // }
      // else if (isset($_SESSION['oa_space_id']) && isset($_SESSION['oa_section_id'])) {
      //   $new_file_node->og_group_ref['und'][0]['target_id'] = $_SESSION['oa_space_id'];
      //   $new_file_node->og_group_ref['und'][0]['field_mode'] = 'default';
      //   $new_file_node->oa_section_ref['und'][0]['target_id'] = $_SESSION['oa_section_id'];
    //  }
      if (isset($element['fid']) && $element['fid'] > 0) {
      $saved_file = file_load($element['fid']);
      $saved_file_name = substr($saved_file->filename, 0, strrpos($saved_file->filename, '.'));
      $new_file_node->title = $saved_file_name;

      $new_file_node->field_drag_and_drop_upload['und'][0]['fid'] = $element['fid'];
      $new_file_node->field_drag_and_drop_upload['und'][0]['display'] = 1;
      
      node_save($new_file_node);
      unset($new_file_node->nid);
      unset($new_file_node->vid);
      
      drupal_set_message(t('You have successfully saved the file @filename', array('@filename' => $saved_file_name)));
    }
  }
}

/**
 * Helper function.
 * Renders the add new subfolder form. Will return an empty array if the user does not have permission to use the form.
 */
function bulk_file_upload_add_taxonomy_term_form($form, &$form_state, $parent_tid) {
  
  $form = array();
  
  if (user_access('access folder add form')) {
    
    $form['parent_tid'] = array(
      '#type' => 'hidden',
      '#value' => $parent_tid,
    );
    
    $form['new_folder_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Click to Add a New Folder'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $parent_folder = taxonomy_term_load($parent_tid);
    $form['new_folder_fields']['preamble'] = array(
      '#type' => 'markup',
      '#markup' => t('Add a new folder within @folder_name', array('@folder_name' => $parent_folder->name)),
    );
    
    $form['new_folder_fields']['term_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Folder Name'),
      '#default_value' => '',
      '#required' => TRUE,
    );
    
    $form['new_folder_fields']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Add Folder'),
    );
    
    $form['#validate'] = array('bulk_file_upload_add_taxonomy_term_form_validate');
    $form['#submit'] = array('bulk_file_upload_add_taxonomy_term_form_submit');
  }
  
  return $form;
}

/**
 * Validation handler.
 * Handles the validation for the add taxonomy form.
 */
function bulk_file_upload_add_taxonomy_term_form_validate($form, &$form_state) {

  // $term = taxonomy_term_load($form_state['values']['parent_tid']);
  // if ($term == FALSE || $term->vocabulary_machine_name != 'file_categories') {
  //   form_set_error('term_name', t('Error: You are trying to add a folder under a restricted folder.'));
  // }
}

/**
 * Submission handler.
 * Handles the validation for the add taxonomy form.
 */
function bulk_file_upload_add_taxonomy_term_form_submit($form, &$form_state) {
  
  $folder_vocab = taxonomy_vocabulary_machine_name_load('file_categories');
  
  $new_folder_term = (object) NULL;
  $new_folder_term->vid = $folder_vocab->vid;
  $new_folder_term->name = $form_state['values']['term_name'];
  $new_folder_term->parent = $form_state['values']['parent_tid'];
  $new_folder_term->vocabulary_machine_name = 'file_categories';
  
  $response = taxonomy_term_save($new_folder_term);
  
  if ($response == SAVED_NEW) {
    drupal_set_message(
      t(
        'You have successfully added the folder @folder_name', 
        array(
          '@folder_name' => $form_state['values']['term_name']
        )
      )
    );
  }
  else {
    drupal_set_message(t('Uh Oh. An error has occured and your new folder could not be added.'), 'error');
  }
}
