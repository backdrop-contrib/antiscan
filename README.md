Antiscan
========

Block IP addresses used by bad crawlers automatically.

**Antiscan** is an add-on module that extends the **IP address blocking** 
module (version 1.x-1.0.5 or newest) to automatically block anyone who 
tries to access restricted paths.

Usually it is a crawler looking for known potentially vulnerable paths, 
such as "wp-admin.php", "xmlrpc.php" and so on.

Installation
------------
Install this module using the official Backdrop CMS instructions at 
https://backdropcms.org/guide/modules

Configuration and usage
-----------------------
Administration page is available via menu *Administration > Configuration > 
User accounts > Antiscan* (admin/config/people/antiscan) 
and may be used for:

- add your patterns for paths to be restricted (some usefull patterns are already added out of the box);
- enable or disable logging for blocked access attempts (enabled by default);
- select the time after which the blocked IP will be unblocked automatically;
- use "Test Mode" to test your patterns, your current IP will not be blocked, but you may see a message when you try to visit the restricted path.

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
