<?php
/**
 * @file
 * notification_link_feature.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function notification_link_feature_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: message_type
  $overrides["message_type.oa_update.message_text|und|1|format"] = 'emailshtml';
  $overrides["message_type.oa_update.message_text|und|1|safe_value"]["DELETED"] = TRUE;
  $overrides["message_type.oa_update.message_text|und|1|value"] = '<p>[message:timestamp:oa_date]</p>
  
  <h3>@{message:user:name} updated <a href=[message:field-oa-node-ref:url]>[message:field-oa-node-ref:title]</a></h3>
  
  <p>[message:field-oa-message-text:value]&nbsp;[message:field-oa-node-ref:oa-log]</p>
  
  <p>!{message:field-oa-node-ref:oa-diff}</p>
  ';
  $overrides["message_type.oa_update.message_text|und|2|safe_value"]["DELETED"] = TRUE;
  $overrides["message_type.oa_update.message_text|und|2|value"] = '<p><a class="oa-userlink" href="[site:url]user/@{message:user:uid}">@{message:user:name}</a> updated <a href="[message:field-oa-node-ref:url]"><strong>[message:field-oa-node-ref:title]</strong></a></p>
  ';
  $overrides["message_type.oa_update.message_text|und|3|safe_value"]["DELETED"] = TRUE;
  $overrides["message_type.oa_update.message_text|und|3|value"] = '<p>@{message:field-oa-node-ref:log}</p>
  ';
  $overrides["message_type.oa_update.message_text|und|4|safe_value"]["DELETED"] = TRUE;
  $overrides["message_type.oa_update.message_text|und|4|value"] = '<p>!{message:field-oa-node-ref:oa-diff}</p>
  ';

 return $overrides;
}
