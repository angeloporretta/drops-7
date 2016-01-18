<?php

/**
 * @file
 * Webform module matrix component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_ranking() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'required' => 1,
    'extra' => array(
      'ranking_col' => '1',
      'ranking_row' => '',
      'title_display' => 0,
      'description' => '',
      'private' => FALSE,
    ),
  );
}



/**
 * Implements _webform_theme_component().
 */
function _webform_theme_ranking() {
  return array(
    'webform_display_ranking' => array(
      'render element' => 'element',
      'file' => 'components/ranking.inc',
      'path' => drupal_get_path('module', 'custom_webforms'),
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_ranking($component) {
  if (!isset($form)) {
    $form = array();
  }

  $form['#tree'] = TRUE;

  $form['extra']['ranking_col_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use numeric columns'),
    '#weight' => 1,
    '#default_value' => isset($component['extra']['ranking_col_type']) ? $component['extra']['ranking_col_type'] : 0,
  );

  $form['extra']['ranking_col'] = array(
    '#type' => 'textfield',
    '#title' => t('Ranking Columns'),
    '#default_value' => isset($component['extra']['ranking_col']) ? $component['extra']['ranking_col'] : "1",
    '#weight' => 2,
    '#parents' => array('extra', 'ranking_col'),
  );

  

  return $form;
}



/**
 * Webform_edit_form extra form elements.
 * @see webform_matrix_component_form_webform_component_edit_form_alter()
 */
function _webform_ranking_component_get_form($form, $form_state, $component) {

  if(!isset($form_state['num_labels'])) {
    $form_state['num_labels'] = sizeof($component['extra']['ranking_fieldset']['num_labels']);
  }
  if (!isset($form_state['num_row_labels'])) {
    $form_state['num_row_labels'] = sizeof($component['extra']['row_fieldset']['num_row_labels']);
  }
  $form['#attached']['css'][] = drupal_get_path('module', 'custom_webforms') . '/css/custom_webforms.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'custom_webforms'). '/js/custom_webforms.js';

  /* START COLUMNS */

  $form['extra']['ranking_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add column labels'),
    '#prefix' => '<div id="ranking-labels-fieldset">',
    '#suffix' => '</div>',
    '#weight' => 2,
  );

  if ($form['extra']['ranking_col_type']['#default_value'] == 0) {
    $form['extra']['ranking_col']['#attributes']['class'] = array('hide-item');
  } else {
    $form['extra']['ranking_fieldset']['#attributes']['class'] = array('hide-item');
  }
  if (!isset($form_state['num_labels']) || empty($form_state['num_labels'])) {
    $form_state['num_labels'] = 1;
  }


  
  for ($i = 0 ; $i < $form_state['num_labels'] ; $i++) {
    $form['extra']['ranking_fieldset']['num_labels'][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Add column label'),
      '#default_value' => isset($component['extra']['ranking_fieldset']['num_labels'][$i]) ? $component['extra']['ranking_fieldset']['num_labels'][$i] : '',
    );
  }

  $form['extra']['ranking_fieldset']['add_more_labels'] = array(
      '#type' => 'submit',
      '#value' => t('Add more labels'),
      '#submit' => array('add_more_labels_ajax'),
      '#validate' => array('add_more_labels_validate'),
      '#ajax' => array(
        'callback' => 'label_ajax_callback',
        'wrapper' => 'ranking-labels-fieldset',
      ),
    );

    if ($form_state['num_labels'] > 1) {
      $form['extra']['ranking_fieldset']['remove_label'] = array(
        '#type' => 'submit',
        '#value' => t('Remove label'),
        '#submit' => array('add_more_labels_ajax_remove'),
        '#validate' => array('remove_label_validate'),
        '#ajax' => array(
          'callback' => 'label_remove_ajax_callback',
          'wrapper' => 'ranking-labels-fieldset',
        ),
      );
    }

  /* END - COLUMNS */

  /* START - ROWS */

  $form['extra']['row_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add row labels'),
    '#prefix' => '<div id="ranking-row-labels-fieldset">',
    '#suffix' => '</div>',
    '#weight' => 3,
  );

  if (!isset($form_state['num_row_labels']) || empty($form_state['num_row_labels'])) {
    $form_state['num_row_labels'] = 1;
  }

  for ($i = 0 ; $i < $form_state['num_row_labels'] ; $i++) {
    $form['extra']['row_fieldset']['num_row_labels'][$i] = array(
      '#type' => 'textfield',
      '#title' => t('Add row label'),
      '#maxlength' => 512,
      '#default_value' => isset($component['extra']['row_fieldset']['num_row_labels'][$i]) ? $component['extra']['row_fieldset']['num_row_labels'][$i] : '',
    );
  }

  $form['extra']['row_fieldset']['add_more_row_labels'] = array(
      '#type' => 'submit',
      '#value' => t('Add label'),
      '#submit' => array('add_more_row_labels_ajax'),
      '#validate' => array('add_more_labels_validate'),
      '#ajax' => array(
        'callback' => 'row_label_ajax_callback',
        'wrapper' => 'ranking-row-labels-fieldset',
      ),
    );

    if ($form_state['num_row_labels'] > 1) {
      $form['extra']['row_fieldset']['remove_row_label'] = array(
        '#type' => 'submit',
        '#value' => t('Remove label'),
        '#submit' => array('add_more_row_labels_ajax_remove'),
        '#validate' => array('remove_label_validate'),
        '#ajax' => array(
          'callback' => 'row_label_remove_ajax_callback',
          'wrapper' => 'ranking-row-labels-fieldset',
        ),
      );
    }

    $form['#attached']['css'][] = array('data' => drupal_get_path('module', 'custom_webforms') . '/css/webform_component.css', 'type' => 'file');

  /* END - ROWS */

  return $form;
}

// /**
//  * Returns matrix_options.
//  *
//  * @see _webform_matrix_component_get_column_form()
//  */
// function _webform_matrix_component_get_type_option(&$form, &$form_state) {
//   return $form['extra']['element'];
// }

/**
 * Implements _webform_render_component().
 */
function _webform_render_ranking($component, $value = NULL, $filter = TRUE) {

  $element = array();
  $element['#weight'] = $component['weight'];
  $element['#webform_component'] = $component;
  if ($component['extra']['title_display'] != 0) {
    $element['value'] = array(
        '#markup' => "<label>" . _webform_filter_xss($component['name']) . "</label>",
    );
  };
  return $element;
}

// /**
//  * Theme for date subcomponent for matrix.
//  */
// function theme_webform_date_matrix($variables) {

//   drupal_add_js(drupal_get_path('module', 'webform') . '/js/webform.js');

//   $element = $variables['element'];

//   $element['year']['#attributes']['class'] = array('year');
//   $element['month']['#attributes']['class'] = array('month');
//   $element['day']['#attributes']['class'] = array('day');

//   // Add error classes to all items within the element.
//   if (form_get_error($element)) {
//     $element['year']['#attributes']['class'][] = 'error';
//     $element['month']['#attributes']['class'][] = 'error';
//     $element['day']['#attributes']['class'][] = 'error';
//   }

//   $class = array('webform-container-inline');

//   // Add the JavaScript calendar if available (provided by Date module package).
//   if (!empty($element['#datepicker'])) {
//     $class[] = 'webform-datepicker';
//     $calendar_class = array('webform-calendar');
//     if ($element['#start_date']) {
//       $calendar_class[] = 'webform-calendar-start-' . $element['#start_date'];
//     }
//     if ($element['#end_date']) {
//       $calendar_class[] = 'webform-calendar-end-' . $element['#end_date'];
//     }
//     $calendar_class[] = 'webform-calendar-day-' . variable_get('date_first_day', 0);

//     $calendar = theme('webform_calendar', array('component' => NULL, 'calendar_classes' => $calendar_class));
//   }

//   $output = '';
//   $output .= '<div class="' . implode(' ', $class) . '">';
//   $output .= drupal_render_children($element);
//   $output .= isset($calendar) ? $calendar : '';
//   $output .= '</div>';

//   return $output;
// }

/**
 * Implements _webform_submit_component().
 */
function _webform_submit_ranking($component, $value) {
  if (isset($value['add_row'])) {
    unset($value['add_row']);
  }
  return serialize($value);
}

// /**
//  * Validate webform_edit_form matrix components.
//  */
// function _webform_matrix_component_edit_select($element, &$form_state) {

//   $lines = explode("\n", trim($element['#value']));
//   $existing_keys = array();
//   $duplicate_keys = array();
//   $missing_keys = array();
//   $long_keys = array();
//   $group = '';
//   foreach ($lines as $line) {
//     $matches = array();
//     $line = trim($line);
//     if (preg_match('/^\<([^>]*)\>$/', $line, $matches)) {
//       $group = $matches[1];
//       // No need to store group names.
//       $key = NULL;
//     }
//     elseif (preg_match('/^([^|]*)\|(.*)$/', $line, $matches)) {
//       $key = $matches[1];
//       if (strlen($key) > 128) {
//         $long_keys[] = $key;
//       }
//     }
//     else {
//       $missing_keys[] = $line;
//     }

//     if (isset($key)) {
//       if (isset($existing_keys[$group][$key])) {
//         $duplicate_keys[$key] = $key;
//       }
//       else {
//         $existing_keys[$group][$key] = $key;
//       }
//     }
//   }

//   if (!empty($missing_keys)) {
//     form_error($element, t('Every option must have a key specified. Specify each option as "safe_key|Some readable option".'));
//   }

//   if (!empty($long_keys)) {
//     form_error($element, t('Option keys must be less than 128 characters. The following keys exceed this limit:') . theme('item_list', $long_keys));
//   }

//   if (!empty($duplicate_keys)) {
//     form_error($element, t('Options within the select list must be unique. The following keys have been used multiple times:') . theme('item_list', array('items' => $duplicate_keys)));
//   }
// }

// /**
//  * Implements _webform_matrix_component_edit_date().
//  */
// function _webform_matrix_component_edit_date($element, $form_state) {
//   // Check if the user filled the required fields.
//   foreach (array('day', 'month', 'year') as $field_type) {
//     if (!is_numeric($element[$field_type]['#value']) && $element['#required']) {
//       form_error($element, t('@name field is required.', array('@name' => $element['#title'])));
//       return;
//     }
//   }
// }

/**
 * Implements _webform_display_component().
 */
function _webform_display_ranking($component, $value, $format = 'html') {
  $unserialized_value = unserialize($value[0]);
  $output_value = array();
  $output_value['field_value'] = $unserialized_value;
  $output_value['rows'] = $component['extra']['row_fieldset']['num_row_labels'];
  if ($component['extra']['rating_col_type'] == 1) {
    for($i = 0; $i < $component['extra']['rating_col']; $i++) {
      $output_value['columns'][$i] = $i+1;
    }
  } else {
    $output_value['columns'] = $component['extra']['ranking_fieldset']['num_labels'];
  }
  return array(
    '#title' => $component['name'],
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_ranking',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#format' => $format,
    '#value' => $output_value,
    '#translatable' => array('title', 'field_prefix', 'field_suffix'),
  );
}

/**
 * Format the text output for this component.
 */
function theme_webform_display_ranking($variables) {
  $output = "<table><thead><th>Row</th><th>Option</th></thead>";
  $output .= '<tbody>';
  foreach($variables['element']['#value']['rows'] as $index => $row) {
    $choice = $variables['element']['#value']['field_value'][$index+1];
    $output .= "<tr><td>" . $row . "</td><td>" . $variables['element']['#value']['columns'][$choice] . "</td></tr>";
  }
  $output .= "</tbody></table>";
  return $output;
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_ranking($component, $sids = array()) {
  // get rows
  $options = $component['extra']['row_fieldset']['num_row_labels'];
  $query = db_select('webform_submitted_data', 'wsd', array('fetch' => PDO::FETCH_ASSOC))
          ->fields('wsd', array('no', 'data'))
          ->condition('nid', $component['nid'])
          ->condition('cid', $component['cid'])
          ->orderBy('sid');

  if (count($sids)) {
    $query->condition('sid', $sids, 'IN');
  }

  $result = $query->execute();
  $analysis_type = _get_analysis_value($component['nid'], $component['cid']);

  $matrixs = array();
  $submissions = 0;
  foreach ($result as $row) {
    $submissions++;
    if ($row['data']) {
      $data = unserialize($row['data']);
      foreach($data as $row_id => $column_id) {
        $matrixs[$row_id][$column_id]++;
      }
    }
  }

  if ($analysis_type == 'Average') {
    foreach($matrixs as $row_id => $rows) {
      $average = 0;
      $sum = 0;

      foreach($rows as $row_value => $row_number) {
        $average += ($row_value + 1) * $row_number;
        $sum += $row_number;
      }
      $average = $average / $sum;
      $items[] = array(0 => $options[$row_id - 1], 1 => $average);
    }
    return array(
      'table_rows' => $items,
      'other_data' => $other,
    );
  } else {
    foreach($matrixs as $row_id => $rows) {
      $sum = 0;

      foreach($rows as $row_value => $row_number) {
        if(is_numeric($row_value)) {
          $sum += $row_number;
        }
      }
      $items[] = array(0 => $options[$row_id - 1], 1 => $sum);
    }
    return array(
      'table_rows' => $items,
      'other_data' => $other,
    );
  }
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_ranking($component, $value) {
  if (isset($value[0]) && !empty($value[0])) {
    $unserialized_value = unserialize($value[0]);
    $output = '';
    foreach($unserialized_value as $row => $option) {
      if ($component['extra']['ranking_col_type'] == 0) {
        if (empty($component['extra']['row_fieldset']['num_row_labels'][$row - 1])) {
          $output .= $component['extra']['ranking_fieldset']['num_labels'][$option] . "\xA";
        } else {
          $output .= $component['extra']['row_fieldset']['num_row_labels'][$row - 1] . ": " . $component['extra']['ranking_fieldset']['num_labels'][$option] . "\xA";
        }
      } else {
        $option = intval($option) + 1;
        if (empty($component['extra']['row_fieldset']['num_row_labels'][$row - 1])) {
          $output .= $option . "\xA";
        } else {
          $output .= $component['extra']['row_fieldset']['num_row_labels'][$row - 1] . ": " . $option . "\xA";
        }
      }
    }
    return $output;
  } else {
    return '';
  }
}

/**
 * Implements _webform_csv_headers_component().
 */
// function _webform_csv_headers_ranking($component, $export_options) {
//   dsm($component);
//   $header = array();
//   $sub_elements = $component['extra']['element'];
//   foreach ($sub_elements as $sub_element) {
//     $header[1][] = check_plain($component['name']);
//     $header[2][] = check_plain($sub_element['title']);
//   }
//   return $header;
// }

/**
 * Implements _webform_csv_data_component().
 */
// function _webform_csv_data_ranking($component, $export_options, $value) {
//   dsm($value);
//   return !isset($value[0]) ? '' : $value[0];
// }

// /**
//  * Unseriaze matrix components values.
//  */
// function _webform_matrix_component_array($value) {
//   return ($value != '') ? unserialize($value) : "";
// }

// /**
//  * Convert matrix select option values to options array.
//  */
// function _webform_matrix_component_select_option_from_text($options) {
//   if ($options != '') {
//     foreach (preg_split("/((\r?\n)|(\r\n?))/", $options) as $line) {
//       if (strstr($line, '|')) {
//         list($key, $value) = explode('|', $line);
//       }
//       else {
//         $key = $value = $line;
//       }
//       $option_array[$key] = $value;
//     }
//   }
//   $option_array = (count($option_array) == 0) ? array(0 => 'None') : $option_array;
//   return $option_array;
// }

// /**
//  * This is simple function to convert array rows to cols.
//  */
// function _webform_matrix_component_array_reverse($array) {
//   $out = array();
//   foreach ($array as $rowkey => $row) {
//     foreach ($row as $colkey => $col) {
//       $out[$colkey][$rowkey] = $col;
//     }
//   }
//   return $out;
// }

// /**
//  * Validate Number
//  */
// function _webform_matrix_component_validate_number($element, &$form_state) {
//   $value = trim($element['#value']);
//   if (!is_numeric($value) && !is_int($value)) {
//     form_error($element, t('Maxlength and Size should be integer.'));
//   }
// }

// function _get_analysis_value($nid, $cid) {
//   $value = db_select('webform_analysis_type', 'w')
//     ->fields('w')
//     ->condition('nid', $nid, '=')
//     ->condition('cid', $cid, '=')
//     ->execute()
//     ->fetchAssoc();  if (!empty($value)) {
//     return $value['analysis_type'];
//   }
//   return 'empty';
// }
