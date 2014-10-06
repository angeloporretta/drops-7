<?php
/**
 * @file: Includes a number of helper functions that can be used by this module or other modules.
 */

/**
 * Helper function.
 * @param array $options: An array options. Valid keys are nids and uids with values of arrays containing nids and uids.
 * @param string $order_by_column: The column to order the result set by. Valid strings are the column names of the file_tracker_downloads table.
 * @param boolean $unique_node: True if you want the a unique result based on the tracked nodes, false otherwise.
 * @return array: An array of file tracker records.
 */
function file_tracker_get_file_node_downloads($options, $order_by_column = '', $unique_node = FALSE) {
  
  $result = array();

  if (!empty($options)) {
    
    $query = db_select('file_tracker_downloads', 'd')->fields('d');
    
    if (isset($options['nids']) && !empty($options['nids'])) {
      $query->condition('d.nid', array($options['nids']), 'IN');
    }
    
    if (isset($options['uids']) && !empty($options['uids'])) {
      $query->condition('d.uid', array($options['uids']), 'IN');
    }
    
    if ($order_by_column != '') {
      $query->orderBy('d.' . $order_by_column, 'desc');
    }
    else {
      $query->orderBy('d.downloaded_timestamp', 'desc');
    }
    
    if ($unique_node == TRUE) {
      $query->groupBy('d.nid');
    }
            
    $result = $query->execute()->fetchAll();
  }
  
  return $result;
}