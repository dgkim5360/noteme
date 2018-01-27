noteme
======

A simple cli-timer with notifications for GNU/Linux Xorg and console

Dependencies
------------

noteme uses the following libraries.

* X11/Xlib.h
* libnotify/notify.h

Installation
------------

::

  $ git clone https://github.com/dgim5360/noteme.git
  $ sudo make install

To install locally, specify the environmental variable ``DESTDIR``, e.g., ::

  $ DESTDIR=~/.local make install

Usage
-----

::

  Usage: noteme [-chmrtu] [title]
  A timer with notifications

  -c bool=0  deliver the note to console, instead of the graphical notification
  -h         print this help message
  -m str=""  message to be delivered
  -r int=1   repeat N times
  -t int=0   time in seconds
  -u int=1   one of urgency levels among 0:low, 1:normal, 2:critical

Example
-------

Running as a daemon (with & at the end) may be most practical usage. ::

  $ noteme -t180 "Tea Time!" -m "After 3 minutes, I shall need a cup of tea..." &
  [1]4500

Then it goes to the background and gives the corresponding PID. We can check the process via ``jobs`` and ``ps``. ::

  $ jobs
  [1]+  Running    noteme -t180 "Tea Time!" -m "After 3 minutes, I shall need a cup of tea..." &
  $ ps
    PID TTY          TIME CMD
   3201 pts/0    00:00:00 bash
   4500 pts/0    00:00:00 noteme
   4549 pts/0    00:00:00 ps

The timer can be stopped and resumed. ::

  $ kill -STOP 4500
  [1]+  Stopped    noteme -t180 "Tea Time!" -m "After 3 minutes, I shall need a cup of tea..."
  $ bg 1
  [1]+  Running    noteme -t180 "Tea Time!" -m "After 3 minutes, I shall need a cup of tea..." &

When the timer expires, the notification pops.
