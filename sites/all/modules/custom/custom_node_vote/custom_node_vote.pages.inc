<?php

// function node_voting_settings_page($form, $form_state, $node) {
//   $form = array();
//   $node_status = _node_vote_get_settings_state(arg(1));
//   if ($node_status == 1) {
//   	$node_value = 1;
//   } else {
//   	$node_value = 0;
//   }
//   $form['allow_voting'] = array(
//   	'#type' => 'checkbox',
//   	'#title' => t('Allow voting for this node'),
//   	'#default_value' => $node_value,
//   );
//   $form['submit'] = array(
//   	'#type' => 'submit',
//   	'#value' => t('Submit'),
//   );
//   $form['#submit'] = array('node_voting_settings_page_submit');
//   return $form;
// }

// function node_voting_settings_page_submit($form, $form_state) {
//   if (arg(0) == 'node' && is_numeric(arg(1))) {
//   	if (_node_vote_get_settings_state(arg(1)) > -1) {
//   	  db_update('node_vote_settings')
//   	    ->fields(array(
//       	  'state' => $form_state['values']['allow_voting'],
//   	  	))
//   		->condition('nid' , arg(1) , '=')
//   		->execute();
//   	} else {
//   	  db_insert('node_vote_settings')
//   	    ->fields(array(
//   	   	  'nid' => arg(1),
//   		  'state' => $form_state['values']['allow_voting'],
//   		  ))
//   		->execute();
//   	}
//   }
// }



?>