<?php
/**
 * @file
 * dragndrop_upload_feature.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function dragndrop_upload_feature_defaultconfig_features() {
  return array(
    'dragndrop_upload_feature' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function dragndrop_upload_feature_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'node-file-field_drag_and_drop_upload'.
  $fields['node-file-field_drag_and_drop_upload'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_drag_and_drop_upload',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'file',
      'settings' => array(
        'display_default' => 0,
        'display_field' => 0,
        'uri_scheme' => 's3',
      ),
      'translatable' => 0,
      'type' => 'file',
    ),
    'field_instance' => array(
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
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Drag and Drop Upload');

  return $fields;
}
