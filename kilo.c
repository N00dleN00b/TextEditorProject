/*** includes ***/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*** defines ***/
#define KILO_VERSION "0.0.1"
#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/
struct editorConfig {
  int screenrows;
  int screencols;
  struct termios orig_termios;
};

struct editorConfig E;

/*** terminal ***/
void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, 

