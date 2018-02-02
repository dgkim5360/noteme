#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <libnotify/notify.h>

#include "noteme.h"

int
noteme_console(const char *title, const char *message, const int sec,
               const int urgency, int repeat) {
  char *color_console;

  switch (urgency) {
    case 0:
      color_console = ANSI_COLOR_LOW;
      break;
    case 1:
      color_console = ANSI_COLOR_NORMAL;
      break;
    case 2:
      color_console = ANSI_COLOR_CRITICAL;
      break;
    default:
      return 1;
  }
  while (repeat--) {
    sleep(sec);
    fprintf(stdout,
            NOTE_CONSOLE_HEAD
            NOTE_CONSOLE_INDENT ANSI_BOLD "%s%s" ANSI_RESET "\n"
            NOTE_CONSOLE_INDENT "%s\n"
            NOTE_CONSOLE_INDENT NOTE_CONSOLE_TAIL,
            color_console,  // for NOTE_CONSOLE_HEAD
            color_console, title,
            message);
  }
  return 0;
}

int
noteme_xorg(const char *title, const char *message, const int sec,
            const int urgency, int repeat) {
  Display *display = XOpenDisplay(NULL);
  NotifyNotification *noteme;

  if (!display)
    return 1;

  notify_init("noteme \u2709");

  while (repeat--) {
    sleep(sec);
    noteme = notify_notification_new(title, message, NULL);
    notify_notification_set_urgency(noteme, urgency);
    notify_notification_show(noteme, NULL);
    g_object_unref(G_OBJECT(noteme));
  }
  if (notify_is_initted())
    notify_uninit();
  XCloseDisplay(display);
  return 0;
}
