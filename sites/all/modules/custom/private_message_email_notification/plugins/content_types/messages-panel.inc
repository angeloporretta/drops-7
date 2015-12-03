<?php

// Plugin definition
$plugin = array(
  'single' => TRUE,
  'title' => t('Envelope'),
  'description' => t('Add the messages envelope'),
  'category' => t('Impetus'),
  'render callback' => 'message_envelope',
  'all contexts' => TRUE,
);

/**
 * Render callback.
 */
function message_envelope($subtype, $conf, $args, $contexts) {
  global $user;
  $block = new stdClass();
  $output = '';
  if($user->uid > 0) {
    $new_messages = db_select('pm_index' , 'p')
      ->fields('p')
      ->condition('recipient' , $user->uid , '=')
      ->condition('deleted' , 0  , '=')
      ->condition('is_new' , 1 , '=')
      ->countQuery()
      ->execute()
      ->fetchField();
    $output .= '<div class="envelope-wrapper">';
    $output .= '<div class="image">';
    $output .= '<a href="/messages">';
    $output .= '<img src="/system/files/content-files/envelope.jpg" />';
    $output .= '</a>';
    $output .= '</div>';
    if ($new_messages > 0) {
      $output .= '<div class="new-messages">';
      $output .= '<span class="new-messages-number">' . $new_messages . '</span>';
      $output .= '</div>';
    }
    $output .= '</div>';
  }
  $block->content = $output;
  return $block;
}

