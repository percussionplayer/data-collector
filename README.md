Data Collector Project
======================

A simple project to collect and distribute video and audio streaming.

## Build
* make (debug): default make. Builds a debug build suitable for GDB debuging.
* make release: regular release build.
* make clean: cleans all build output.
* sudo make install: installs release binary to /usr/local/bin and startup script to /etc/init.d
* sudo make uninstall: removes installed binary and startup script
* By default, builds in a "quiet" mode that only lists the actions being performed. By passing V=true to make, you can compile in verbose mode to see the full compiler commands being issued.

## Versioning
A git tag in the format of "vMAJOR.MINOR.PATCH-description" will create several pre-processor macros describing the version. MAJOR, MINOR, and PATCH should be numeric.

## Execution
The "data-collector" script in the scripts folder (installed to /etc/init.d) manages the execution of the data collector:
* /etc/init.d/data-collector start: runs the Data Collector. Searches for the binary first in /usr/local/bin, then in the current directory.
* /etc/init.d/data-collector stop: stops the Data Collector.
* /etc/init.d/data-collector status: reports the current running status of the Data Collector.
* /etc/init.d/data-collector restart: stops and restarts the Data Collector.

## Logging
The Data Collector logs to the syslog. Log entries can be viewed using 'journalctl -t data-collector'.
