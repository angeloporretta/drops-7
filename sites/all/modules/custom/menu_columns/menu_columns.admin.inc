<?php

  function set_menu_items_per_column() {
  	$form = array();

    $form['set_items_per_column'] = array(
        '#type' => 'textfield',
        '#title' => t('Please set the number of items per column'),
        '#default_value' => variable_get('column_items', ''),
        '#description' => t("Here you can set the number of items per column"),
        '#required' => TRUE,
    );
    $form['#submit'][] = 'menu_items_submit';
    
		return system_settings_form($form);
  }

  function menu_items_submit($form, $form_state) {
  	variable_set('column_items' , $form_state['values']['set_items_per_column']);
  }

?>