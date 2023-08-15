#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "slms.h"

static char BUFFER[BUFSIZ];

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
  return i;
}

int prompt(int n, const char* s)
{
  /* todo: move cursor to insertion area */
  /* before print s and readline */
  movecur(1, MAXHEIGHT);
  prints(s);
  return readline(n);
}
