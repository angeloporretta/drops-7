<?php
/**
 * @file
 * redirect_user_after_login.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function redirect_user_after_login_default_rules_configuration() {
  $items = array();
  $items['rules_redirect_user_after_login'] = entity_import('rules_config', '{ "rules_redirect_user_after_login" : {
      "LABEL" : "Redirect user after login",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "login" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_login" : [] },
      "DO" : [ { "redirect" : { "url" : "user\\/[account:uid]\\/view" } } ]
    }
  }');
  return $items;
}
