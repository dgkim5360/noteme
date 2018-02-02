#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include "noteme.h"
#define HELP "\nUsage: noteme [-chmrtu] [title]\n"\
  "A timer with notifications\n\n"\
  "-c bool=0  deliver the note to console, instead of the graphical notification\n"\
  "-h         print this help message\n"\
  "-m str=\"\"  message to be delivered\n"\
  "-r int=1   repeat N times\n"\
  "-t int=0   time in seconds\n"\
  "-u int=1   one of urgency levels among 0:low, 1:normal, 2:critical\n"
#define HELP_TITLE "\x1b[91mAt least the title should be specified.\x1b[0m\n"
#define HELP_XORG "\x1b[91mX server is not running.\x1b[0m\n"
#define HELP_REPEAT "\x1b[91mThe repeat number should be an integer.\x1b[0m\n"
#define HELP_TIME "\x1b[91mThe seconds to wait should be an integer.\x1b[0m\n"
#define HELP_URGENCY "\x1b[91mThe urgency level should be 0, 1, or 2.\x1b[0m\n"

bool is_arg_num(const char *);

int main(const int argc, char *argv[]) {
  char c, *title = NULL, *message = NULL;
  int sec = 0, level = 1, repeat = 1;
  bool to_console = false;

  if (argc == 1) {
    fprintf(stderr, HELP_TITLE);
    fprintf(stdout, HELP);
    return 1;
  }

  while ((c = getopt(argc, argv, "chm:r:t:u:")) != -1) {
    switch (c) {
      case 'c':
        to_console = true;
        break;
      case 'm':
        message = optarg;
        break;
      case 'h':
        fprintf(stdout, HELP);
        return 0;
      case 'r':
        if (!is_arg_num(optarg)) {
          fprintf(stderr, HELP_REPEAT);
          fprintf(stdout, HELP);
          return 1;
        }
        repeat = atoi(optarg);
        break;
      case 't':
        if (!is_arg_num(optarg)) {
          fprintf(stderr, HELP_TIME);
          fprintf(stdout, HELP);
          return 1;
        }
        sec = atoi(optarg);
        break;
      case 'u':
        if (!is_arg_num(optarg)) {
          fprintf(stderr, HELP_URGENCY);
          fprintf(stdout, HELP);
          return 1;
        }
        if ((level = atoi(optarg)) < 0 || level > 2) {
          fprintf(stderr, HELP_URGENCY);
          fprintf(stdout, HELP);
          return 1;
        }
        break;
      case '?':
      default:
        printf(HELP);
        return 0;
    }
  }
  if (optind >= argc) {
    fprintf(stderr, HELP_TITLE);
    fprintf(stdout, HELP);
    return 1;
  }

  title = argv[optind];

  if (to_console) {
    if (noteme_console(title, message, sec, level, repeat)) {
      fprintf(stderr, HELP_URGENCY);
      fprintf(stdout, HELP);
      return 1;
    }
  }
  else {
    if (noteme_xorg(title, message, sec, level, repeat)) {
      fprintf(stderr, HELP_XORG);
      return 1;
    }
  }

  return 0;
}

bool is_arg_num(const char *optarg) {
  int i;

  for (i = 0; *(optarg+i) != '\0'; ++i)
    if (!isdigit(*(optarg+i)))
      return false;
  return true;
}
