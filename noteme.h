#define NOTE_CONSOLE_HEAD "\n\n\u2709 ======\n  %snoteme\x1b[0m\n  ======\n"
#define NOTE_CONSOLE_TAIL "============ \u2709\n\n"
#define NOTE_CONSOLE_INDENT "  "

#define ANSI_BOLD "\x1b[1m"
#define ANSI_COLOR_LOW ""
#define ANSI_COLOR_NORMAL "\x1b[94m"
#define ANSI_COLOR_CRITICAL "\x1b[91m"
#define ANSI_RESET "\x1b[0m"

int noteme_console(const char *, const char *, const int, const int, int);
int noteme_xorg(const char *, const char *, const int, const int, int);
