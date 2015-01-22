<?php
/**
 * @file
 * dragndrop_upload_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function dragndrop_upload_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-file-field_drag_and_drop_upload'
  $field_instances['node-file-field_drag_and_drop_upload'] = array(
    'bundle' => 'file',
    'comment_alter' => 0,
    'default_value' => array(),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 4,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_drag_and_drop_upload',
    'label' => 'Drag and Drop Upload',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'jpg roq mxf asf yuv avi mng drc ogv ogg mkv webm flv qt rm wmv mp4 m4p m4v mpg mp2 mpeg mp ai ppt pptx doc docx jpeg png xls xlsx',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'dragndrop_upload_file',
      'settings' => array(
        'allow_replace' => 0,
        'droppable_area_text' => 'Drop files here to upload',
        'media_browser' => 0,
        'multiupload' => 1,
        'progress_indicator' => 'throbber',
        'standard_upload' => 1,
        'upload_button_text' => 'Upload',
        'upload_event' => 'manual',
      ),
      'type' => 'dragndrop_upload_file',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Drag and Drop Upload');

  return $field_instances;
}
