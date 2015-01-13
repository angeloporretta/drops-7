<?php
/**
 * @file
 * amazon_file_field.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function amazon_file_field_defaultconfig_features() {
  return array(
    'amazon_file_field' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function amazon_file_field_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'node-file-field_upload_file_big_files'.
  $fields['node-file-field_upload_file_big_files'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_upload_file_big_files',
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
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'file',
          'settings' => array(),
          'type' => 'file_default',
          'weight' => 5,
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
      'field_name' => 'field_upload_file_big_files',
      'label' => 'Upload File(big files)',
      'required' => 0,
      'settings' => array(
        'description_field' => 0,
        'file_directory' => '',
        'file_extensions' => 'jpg roq mxf asf yuv avi mng drc ogv ogg mkv webm flv qt rm wmv mp4 m4p m4v mpg mp2 mpeg mp',
        'max_filesize' => '200 MB',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'amazons3_cors',
        'settings' => array(
          's3_acl' => 'public-read-write',
        ),
        'type' => 'amazons3_cors',
        'weight' => 2,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Upload File(big files)');

  return $fields;
}
