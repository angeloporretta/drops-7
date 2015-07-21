<?php
/**
 * @file
 * webform_report_export.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function webform_report_export_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_access_sections|node|webform_report|form';
  $field_group->group_name = 'group_access_sections';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform_report';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sections',
    'weight' => '41',
    'children' => array(
      0 => 'field_oa_group_ref',
      1 => 'oa_section_ref',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-access-sections field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_access_sections|node|webform_report|form'] = $field_group;

  return $export;
}
