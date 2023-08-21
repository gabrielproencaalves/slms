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

  if (c == EOF && i == 0)
    return EOF;

  BUFFER[i] = '\0';
  setx(1);
  sety(gety() + 1);

  return i;
}

int prompt(int n, const char* s)
{
  int retval;
  int x_pos;
  int y_pos;

  x_pos = getx();
  y_pos = gety();

  movecur(1, MAXHEIGHT);
  clearl();
  prints(s);
  retval = readline(n);
  movecur(x_pos, y_pos);

  return retval;
}
