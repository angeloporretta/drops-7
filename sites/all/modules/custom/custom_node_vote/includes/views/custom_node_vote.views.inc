<?php

/**
 * Implements hook_views_data().
 */
function custom_node_vote_views_data()
{
 
    $data = array();
 
    $data['node_vote']['table']['group'] = t('Node Vote');
 
    $data['node_vote']['table']['base'] = array(
        'title' => t('Node Vote'),
        'help' => t('Contains votes for comments'),
    );

    $data['node_vote']['table']['join'] = array(
      'comment' => array(
        'left_field' => 'cid',
        'field' => 'cid',
      ),
	);
 	
    // The CID field
	$data['node_vote']['cid'] = array(
      'title' => t('CID'),
      'help' => t('The record CID.'),
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
        'base' => 'comment',
        'field' => 'cid',
        'handler' => 'views_handler_relationship',
        'label' => t('Comment'),
      ),
	);

	// The UID field
	$data['node_vote']['uid'] = array(
      'title' => t('UID'),
      'help' => t('The record UID.'),
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
        'base' => 'user',
        'field' => 'uid',
        'handler' => 'views_handler_relationship',
        'label' => t('User'),
      ),
	);

	// The VALUE field
	$data['node_vote']['value'] = array(
      'title' => t('VALUE'),
      'help' => t('The record value.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
	);

    return $data;
 
}