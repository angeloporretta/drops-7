<?php
/**
 * @file
 * amazon_file_field.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function amazon_file_field_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-file-field_upload_file_big_files'
  $field_instances['node-file-field_upload_file_big_files'] = array(
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
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Upload File(big files)');

  return $field_instances;
}
