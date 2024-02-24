Antiscan
========

Automatically block (ban) IP addresses used by bad crawlers or vulnerability scanners.

**Antiscan** is an add-on module that extends the [IP Address Blocking](https://backdropcms.org/project/ip_blocking)
module (version 1.x-1.0.5 or newer) to automatically block anyone trying to access restricted paths.

Usually this is a bad crawler looking for known potentially vulnerable paths,
such as "wp-admin.php", "xmlrpc.php" and so on.

Also, since version 1.x-1.0.5, you can block bad robots using their well-known User-Agent strings and spam referrer domains.

**New in version 1.x-1.0.4:** option "Report to AbuseIPDB" can be enabled for automatic reporting to AbuseIPDB about blocked scanner's activity.
You need to install [AbuseIPDB report](https://backdropcms.org/project/abuseipdb_report) module to see and use this option.

Installation
------------
Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules

Configuration and usage
-----------------------
The administration page is available from *Administration > Configuration >
User accounts > Antiscan* menu (admin/config/people/antiscan)
and can be used to:

- add your patterns for paths to be restricted (some useful patterns are already added out of the box);
- specify paths or parts of paths that will NOT be restricted to avoid self-blocking;
- set "User-Agent strings" to be blocked;
- set "Referrer spam domains" to be blocked;
- enable automatic reporting to AbuseIPDB about blocked scanner activity ("AbuseIPDB report" module should be installed);
- enable logging of blocked access attempts (enabled by default);
- select the time after which the blocked IP will be automatically unblocked;
- use "Test Mode" to test your patterns, your current IP will not be blocked, instead you can see a message when you try to visit the restricted path;
- for locations with many people sharing the same IP: you can set threshold limit for wrong attempts.

This module also provides a block with information about the number of currently blocked IP addresses.
You can place this block anywhere you like (for users with 'antiscan settings' permission).

**Screenshots** are available at https://findlab.net/projects/antiscan

Known issues
------------
Sometimes you may see in log messages like this:
> "Warning: Cannot modify header information - headers already sent by (output started at /core/includes/bootstrap.inc:3133) in antiscan_action() (line 164 of /modules/antiscan/antiscan.module)"

Here is the explanation.

When Backdrop served a cached page, the 'X-Backdrop-Cache: HIT' and 'cache-control' headers were sent with the obsolete entries before they were actually generated for the request.

To avoid such messages and incorrect module actions (in such cases can not get in time to reject blocked IP) you have two options:

- you can disable prefetching for cached pages: go to 'admin/config/development/performance' and within the 'Caching' fieldset uncheck the 'Use background fetch for cached pages' checkbox, then press the 'Save configuration' button;
- add the option '$settings['page_cache_invoke_hooks'] = TRUE;' to your 'settings.php' file.

Disabling prefetching for cached pages (first option) is sufficient to avoid such collisions in most cases.

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainer
------------------
Vladimir (https://github.com/findlabnet/)

More information
----------------
For bug reports, feature or support requests, please use the module
issue queue at https://github.com/backdrop-contrib/antiscan/issues.
