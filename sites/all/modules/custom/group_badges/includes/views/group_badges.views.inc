<?php

/**
 * Implements hook_views_data().
 */
function group_badges_views_data()
{
 
    $data = array();
 
    $data['badges_group']['table']['group'] = t('Badge Group');
 
    $data['badges_group']['table']['base'] = array(
      'title' => t('Badge Group'),
      'help' => t('Contains the group a badge is assigned to'),
    );

    $data['badges_group']['table']['join'] = array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
      'user_badges_badges' => array(
        'left_field' => 'bid',
        'field' => 'bid',
      ),
	  );
 	
    // The BID field
	$data['badges_group']['bid'] = array(
      'title' => t('Bid'),
      'help' => t('The badge ID.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'relationship' => array(
        'base' => 'user_badges_badges',
        'field' => 'bid',
        'handler' => 'views_handler_relationship',
        'label' => t('User Badge'),
      ),
	);

	// The NID field
	$data['badges_group']['nid'] = array(
      'title' => t('Nid'),
      'help' => t('The badge group id.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'relationship' => array(
        'base' => 'node',
        'field' => 'nid',
        'handler' => 'views_handler_relationship',
        'label' => t('Node'),
      ),
	);

    return $data;
 
}