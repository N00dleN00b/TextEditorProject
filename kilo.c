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

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &E.orig_termios);
  atexit(disableRawMode);
  
  struct termios raw = E.orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int getWindowSize(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}

/*** append buffer ***/
struct abuf {
  char *b;
  int len;
};

#define ABUF_INIT {NULL, 0}

void abAppend(struct abuf *ab, const char *s, int len) {
  char *new = realloc(ab->b, ab->len + len);
  if (new == NULL) return;
  memcpy(&new[ab->len], s, len);
  ab->b = new;
  ab->len += len;
}

void abFree(struct abuf *ab) {
  free(ab->b);
}

/*** output ***/
void editorDrawRows(struct abuf *ab) {
  int y;
  for (y = 0; y < E.screenrows; y++) {
    if (y == E.screenrows / 3) {
      char welcome[80];
      int welcomelen = snprintf(welcome, sizeof(welcome),
        "Kilo editor -- version %s", KILO_VERSION);
      if (welcomelen > E.screencols) welcomelen = E.screencols;

      int padding = (E.screencols - welcomelen) / 2;
      if (padding) {
        abAppend(ab, "~", 1);
        padding--;
      }
      while (padding--) abAppend(ab, " ", 1);
      abAppend(ab, welcome, welcomelen);
    } else {
      abAppend(ab, "~", 1);
    }

    abAppend(ab, "\x1b[K", 3);  // Clear the line
    if (y < E.screenrows - 1) {
      abAppend(ab, "\r\n", 2);  // Avoid adding a blank line at the bottom
    }
  }
}

void editorRefreshScreen() {
  struct abuf ab = ABUF_INIT;
  abAppend(&ab, "\x1b[?25l", 6);  // Hide cursor
  abAppend(&ab, "\x1b[H", 3);  // Move cursor to top-left
  editorDrawRows(&ab);
  abAppend(&ab, "\x1b[H", 3);  // Move cursor back to top-left
  abAppend(&ab, "\x1b[?25h", 6);  // Show cursor
  write(STDOUT_FILENO, ab.b, ab.len);
  abFree(&ab);
}

/*** input ***/
void editorProcessKeypress() {
  char c = getchar();
  if (c == CTRL_KEY('q')) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    exit(0);
  }
}

/*** init ***/
void initEditor() {
  if (getWindowSize(&E.screenrows, &E.screencols) == -1) {
    die("getWindowSize");
  }
}

int main() {
  enableRawMode();
  initEditor();

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}
