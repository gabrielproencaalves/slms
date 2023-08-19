#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "slms.h"

char BUFFER[BUFSIZ];

int readline(int n)
{
  char c;
  int i = 0;

  if (n == 0)
    n = BUFSIZ;

  while ((c = getchar()) != EOF && c != '\n' && i < n) {
    BUFFER[i++] = c;
  }

  BUFFER[i] = '\0';
  setx(1);
  sety(gety() + 1);

  return i;
}

int prompt(int n, const char* s)
{
  /* todo: move cursor to insertion area */
  /* before print s and readline */
  int retval;
  int x_pos;
  int y_pos;

  x_pos = getx();
  y_pos = gety();

  movecur(1, MAXHEIGHT);
  prints(s);
  retval = readline(n);
  movecur(x_pos, y_pos);

  return retval;
}
