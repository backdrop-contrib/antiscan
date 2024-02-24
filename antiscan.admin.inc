<?php
/**
 * @file
 * Admin form to manage module settings
 *
 */

/**
 * Define the form for manage blocking restricted paths, User-Agents and referrers
 *
 */
function antiscan_form($form, &$form_state) {
  $config = config('antiscan.settings');

  $form['top'] = array(
    '#markup' => t('If a web crawler or even a person (except for logged in users) tries to visit a path that matches one of the patterns specified in the fields below, their IP address will be blocked')
      . ' <u>' . t('immediately without warning') . '</u> ' . t('if the threshold number of attempts is not specified below.'),
  );

  $url = url('admin/config/people/ip-blocking');
  $form['info'] = array(
    '#markup' => '<p>'. t('You can manage blocked IPs at  <a href="@url">this page</a>.', array('@url' => $url)) . '</p>',
  );

  $path_patterns = $config->get('path_patterns');
  $form['path_patterns'] = array(
    '#type' => 'textarea',
    '#rows' => 5,
    '#columns' => 60,
    '#default_value' => $path_patterns,
    '#title' => t('Restricted path patterns'),
    '#required' => TRUE,
    '#description' => t('Enter paths or portions of paths to restrict, separating them with commas or new lines.')
      . '<br>' . t('The <b>*</b> character is a wildcard for end of the pattern, so pattern like') . '<b> /wp-* </b>'
      . t('will match to any path containing "/wp-admin", "/wp-login.php", etc.'),

  );

  $form['noblock'] = array(
    '#type' => 'fieldset',
    '#title' => t('Non-blockable path patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $path_noblock = $config->get('path_noblock');
  $form['noblock']['path_noblock'] = array(
    '#type' => 'textarea',
    '#title' => t('Non-blockable path patterns'),
    '#rows' => 5,
    '#columns' => 60,
    '#default_value' => $path_noblock,
    '#required' => TRUE,
    '#description' => t('Enter paths or portions of paths that will NOT be restricted to avoid self-blocking for users.')
      . '<br>' . t('Same format of rules as above.'),
  );

  $threshold_enabled = $config->get('threshold_enabled');
  $threshold_limit   = $config->get('threshold_limit');
  $threshold_window  = $config->get('threshold_window');

  if ($threshold_enabled) {
    $threshold = $threshold_limit . ' ' . t('time(s) per') . ' ' . $threshold_window . ' ' . t('seconds');
  }
  else {
    $threshold = t('not specified');
  }

  $form['threshold'] = array(
    '#type' => 'fieldset',
    '#title' => t('Threshold limit and window:') . ' ' . $threshold,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['threshold']['threshold_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable restricted path threshold:') . '&nbsp;',
    '#default_value' => $threshold_enabled,
    '#prefix' => '<div style="display:inline-flex;align-items:center;column-gap:1rem">'
  );

  $form['threshold']['threshold_limit'] = array(
    '#type' => 'number',
    '#title_display' => 'after',
    '#title' => t('attempt(s) as limit') . ';',
    '#default_value' => $threshold_limit,
    '#min' => 1,
    '#max' => 10,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-10')),
    '#states' => array(
      'disabled' => array(
        ':input[name="threshold_enabled"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['threshold']['threshold_window'] = array(
    '#type' => 'number',
    '#title_display' => 'after',
    '#title' => t('seconds as window') . '.',
    '#suffix' => '</div>',
    '#default_value' => $threshold_window,
    '#min' => 1,
    '#max' => 7200,
    '#step' => 1,
    '#attributes' => array('title' => array('values 1-7200')),
    '#states' => array(
      'disabled' => array(
        ':input[name="threshold_enabled"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['threshold']['description'] = array(
    '#markup' => '<hr><ul><li>' . t('threshold limit - the number of times an IP address can access restricted path during the threshold window before they are blocked;') . '</li>'
    . '<li>' . t('threshold window - the time period in which to consider attacks. 3600 seconds is one hour.') . '</li></ul>'
  );

  $blocked_ua = $config->get('blocked_ua');
  $form['blocked_ua'] = array(
    '#type' => 'textarea',
    '#rows' => 5,
    '#columns' => 60,
    '#default_value' => $blocked_ua,
    '#title' => t('Blockable User-Agent strings'),
    '#description' => t('Enter User-Agent strings to block, one per line.')
      . '<br>' . t('The <b>*</b> character is a wildcard for end of the string, so pattern like') . '<b> python-requests/* </b>'
      . t('will block any User-Agent strings starting with "python-requests/", for example "python-requests/2.9.0".'),
    '#element_validate' => array('_validate_self_ua'),
  );

  $blocked_referrer = $config->get('blocked_referrer');
  $form['blocked_referrer'] = array(
    '#type' => 'textarea',
    '#rows' => 5,
    '#columns' => 60,
    '#default_value' => $blocked_referrer,
    '#title' => t('Blockable referrer spam domains'),
    '#description' => t('Enter referrer spam domains to block, separating them with commas or new lines.')
      . '<br>' . t('Use domain name only, for example: "semalt.com" or "buttons-for-website.com" without quotes.'),
    '#element_validate' => array('_validate_self_referrer'),
  );

  $form['unblock'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unblock blocked IPs automatically after:') . '&nbsp;',
    '#default_value' => $config->get('unblock'),
    '#prefix' => '<div style="display:inline-flex;align-items:center">'
  );
  $form['unblock_after'] = array(
    '#type' => 'select',
    '#options' => array(
      900 => t('15 minutes'),
      3600 => t('60 minutes'),
      43200 => t('12 hours'),
      86400 => t('24 hours'),
      604800 => t('7 days'),
      2592000 => t('30 days'),
      31536000 => t('365 days'),
    ),
    '#default_value' => $config->get('unblock_after'),
    '#suffix' => '</div>',
    '#states' => array(
      'disabled' => array(
        ':input[name="unblock"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['log_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => $config->get('log_enabled'),
    '#description' => t('Enable logging of blocked access attempts.'),
  );

  if (module_exists('abuseipdb_report')) {
    $form['abuseipdb_report'] = array(
      '#type' => 'checkbox',
      '#title' => t('Report to AbuseIPDB'),
      '#default_value' => $config->get('abuseipdb_report'),
      '#description' => t('Report to AbuseIPDB about blocked scanners activity.'),
    );
  }

  $form['test_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Test mode'),
    '#default_value' => $config->get('test_mode'),
    '#description' => t('Turn it on to test your patterns. Your IP address will not be blocked, but you can see a blocking message when you try to visit a path that contains a restricted path pattern.'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Implements hook_validate().
 */
function antiscan_form_validate($form, &$form_state) {
  $config         = config('antiscan.settings');
  $path_noblock   = $config->get('path_noblock');
  $path_patterns  = trim($form_state['values']['path_patterns']);

  $noblock_array  = _textarea_to_array($path_noblock);
  $patterns_array = _textarea_to_array($path_patterns);
  $matched        = array_intersect($noblock_array, $patterns_array);

  if (!empty($matched)) {
    $matched_patterns = implode(", ", $matched);
    form_set_error('path_patterns', t('You cannot use "%matched_patterns" for a pattern. Please verify "Not blockable path patterns" under "Additional settings" below.', array('%matched_patterns' => $matched_patterns)));
  }
}

/**
 * Implements hook_submit().
 */
function antiscan_form_submit($form, &$form_state) {
  $config            = config('antiscan.settings');
  $path_patterns     = trim($form_state['values']['path_patterns']);
  $path_noblock      = trim($form_state['values']['path_noblock']);
  $blocked_ua        = trim($form_state['values']['blocked_ua']);
  $blocked_referrer  = trim($form_state['values']['blocked_referrer']);
  $log_enabled       = (int) $form_state['values']['log_enabled'];
  $unblock           = (int) $form_state['values']['unblock'];
  $unblock_after     = (int) $form_state['values']['unblock_after'];
  $test_mode         = (int) $form_state['values']['test_mode'];
  $threshold_enabled = (int) $form_state['values']['threshold_enabled'];
  $threshold_limit   = (int) $form_state['values']['threshold_limit'];
  $threshold_window  = (int) $form_state['values']['threshold_window'];

  $config->set('path_patterns',     strtolower($path_patterns));
  $config->set('path_noblock',      strtolower($path_noblock));
  $config->set('blocked_ua',        $blocked_ua);
  $config->set('blocked_referrer',  strtolower($blocked_referrer));
  $config->set('threshold_enabled', $threshold_enabled);
  $config->set('threshold_limit',   $threshold_limit);
  $config->set('threshold_window',  $threshold_window);

  if (isset($form_state['values']['abuseipdb_report'])) {
    $config->set('abuseipdb_report', $form_state['values']['abuseipdb_report']);
  }

  $config->set('log_enabled',   $log_enabled);
  $config->set('unblock',       $unblock);
  $config->set('unblock_after', $unblock_after);
  $config->set('test_mode',     $test_mode);

  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}

/**
 * Make sure that user own UA is not being blocked.
 * @param type $element
 * @param type $form_state
 */
function _validate_self_ua($element, &$form_state) {
  $current_ua = $_SERVER['HTTP_USER_AGENT'];
  $blocked_ua = trim($form_state['values']['blocked_ua']);

  if (!empty($blocked_ua)) {
    $u_agents = _textarea_to_array($blocked_ua, FALSE);

    foreach ($u_agents as $u_agent) {
      if (substr($u_agent, -1) == '*') {
        $u_agent = substr($u_agent, 0, -1);

        if (strpos($current_ua, $u_agent) !== FALSE) {
          form_error($element, t('You are trying to add the part of User-Agent string that matches to your own current User-Agent string!')
            . '<br>' . t('Your User-Agent: ') . $current_ua
            . '<br>' . t('Trying to block: ') . $u_agent . '*');
        }
      }
      else {
        if ($u_agent == $current_ua) {
          form_error($element, t('You are trying to add your own current User-Agent string!')
            . '<br>' . t('Your User-Agent: ') . $current_ua
            . '<br>' . t('Trying to block: ') . $u_agent);
        }
      }
    }
  }
}

/**
 * Make sure the host of this site is not blocked..
 * @param type $element
 * @param type $form_state
 */
function _validate_self_referrer($element, &$form_state) {
  $blocked_referrer = trim($form_state['values']['blocked_referrer']);
  $host             = $_SERVER['HTTP_HOST'];

  if (!empty($blocked_referrer)) {
    $referrers = _textarea_to_array($blocked_referrer);

    foreach ($referrers as $referrer) {
      if (strpos($host, $referrer) !== FALSE) {
        form_error($element, t('You are trying to add your own host to referrer spam domains!')
          . '<br>' . t('Your hostname: ') . $host
          . '<br>' . t('Trying to block: ') . $referrer);
      }
    }
  }
}
