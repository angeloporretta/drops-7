<?php
/**
 * @file
 * notification_link_feature.features.inc
 */

/**
 * Implements hook_default_message_type_alter().
 */
function notification_link_feature_default_message_type_alter(&$data) {
  if (isset($data['oa_update'])) {
    $data['oa_update']->message_text['und'][1]['format'] = 'emailshtml'; /* WAS: 'full_html' */
    $data['oa_update']->message_text['und'][1]['value'] = '<p>[message:timestamp:oa_date]</p>
    
    <h3>@{message:user:name} updated <a href=[message:field-oa-node-ref:url]>[message:field-oa-node-ref:title]</a></h3>
    
    <p>[message:field-oa-message-text:value]&nbsp;[message:field-oa-node-ref:oa-log]</p>
    
    <p>!{message:field-oa-node-ref:oa-diff}</p>
    '; /* WAS: '[message:timestamp:oa_date]<br /><h3>@{message:user:name} updated <a href="[message:field-oa-node-ref:url]">[message:field-oa-node-ref:title]</a></h3>
    <p>[message:field-oa-message-text:value]&nbsp;[message:field-oa-node-ref:oa-log]</p><p>!{message:field-oa-node-ref:oa-diff}</p>' */
    $data['oa_update']->message_text['und'][2]['value'] = '<p><a class="oa-userlink" href="[site:url]user/@{message:user:uid}">@{message:user:name}</a> updated <a href="[message:field-oa-node-ref:url]"><strong>[message:field-oa-node-ref:title]</strong></a></p>
    '; /* WAS: '<a href="[site:url]user/@{message:user:uid}" class="oa-userlink">@{message:user:name}</a> updated <a href="[message:field-oa-node-ref:url]"><strong>[message:field-oa-node-ref:title]</strong></a>' */
    $data['oa_update']->message_text['und'][3]['value'] = '<p>@{message:field-oa-node-ref:log}</p>
    '; /* WAS: '@{message:field-oa-node-ref:log}' */
    $data['oa_update']->message_text['und'][4]['value'] = '<p>!{message:field-oa-node-ref:oa-diff}</p>
    '; /* WAS: '!{message:field-oa-node-ref:oa-diff}' */
    unset($data['oa_update']->message_text['und'][1]['safe_value']);
    unset($data['oa_update']->message_text['und'][2]['safe_value']);
    unset($data['oa_update']->message_text['und'][3]['safe_value']);
    unset($data['oa_update']->message_text['und'][4]['safe_value']);
  }
}
