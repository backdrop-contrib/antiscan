Antiscan
========

Automatic block (ban) IP addresses used by bad crawlers or vulnerability scanners.

**Antiscan** is an add-on module that extends the [IP address blocking](https://backdropcms.org/project/ip_blocking) 
module (version 1.x-1.0.5 or newest) to automatically block anyone who tries to access paths defined as restricted.

Usually it is a bad crawler looking for known potentially vulnerable paths, 
such as "wp-admin.php", "xmlrpc.php" and so on.

Also, since version 1.x-1.0.5, you can block bad bots using their well-known User-Agent strings and spam referrer domains.

**New in version version 1.x-1.0.4:** option "Report to AbuseIPDB" can be enabled for automatic reporting to AbuseIPDB about blocked scanners activity.    
You need to install [AbuseIPDB report](https://backdropcms.org/project/abuseipdb_report) module to see and use this option.

Installation
------------
Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules

Configuration and usage
-----------------------
Administration page is available via menu *Administration > Configuration > 
User accounts > Antiscan* (admin/config/people/antiscan) 
and may be used for:

- add your patterns for paths to be restricted (some usefull patterns are already added out of the box);
- set paths or portions of paths that will NOT be restricted to avoid self-blocking;
- set User-Agent strings, to be blocked;
- set Referrer spam domains to be blocked;
- enable automatic reporting to AbuseIPDB about blocked scanners activity ("AbuseIPDB report" module should be installed);
- enable logging for blocked access attempts (enabled by default);
- select the time after which the blocked IP will be unblocked automatically;
- use "Test Mode" to test your patterns, your current IP will not be blocked, but you may see a message when you try to visit the restricted path.

Also, this module provides a block with information about the number of currently blocked IP addresses.
You can place this block in any convenient place.

**Screenshots** are available at https://findlab.net/projects/antiscan

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
