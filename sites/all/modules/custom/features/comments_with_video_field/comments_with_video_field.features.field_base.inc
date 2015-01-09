<?php
/**
 * @file
 * comments_with_video_field.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function comments_with_video_field_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_video_upload'
  $field_bases['field_video_upload'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_video_upload',
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
    'module' => 'video',
    'settings' => array(
      'autoconversion' => 1,
      'autothumbnail' => 'auto',
      'default_video_thumbnail' => array(
        'fid' => 0,
        'remove_button' => 'Remove',
        'upload' => '',
        'upload_button' => 'Upload',
      ),
      'presets' => array(
        'FLV' => 0,
        'Mp4' => 0,
        'Ogg' => 0,
        'Ogv' => 0,
        'WebM' => 0,
      ),
      'preview_video_thumb_style' => 'thumbnail',
      'thumbnail_format' => 'jpg',
      'uri_scheme' => 's3',
      'uri_scheme_converted' => 's3',
      'uri_scheme_thumbnails' => 'private',
    ),
    'translatable' => 0,
    'type' => 'video',
  );

  return $field_bases;
}
