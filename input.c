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
  bool inside = true;

  if (n == 0)
    n = BUFSIZ;

  while ((c = getchar()) == ' ' || c == '\t');

  n--;
  while (c != EOF && c != '\n' && i < n)
    {
      if (c != ' ' && c != '\t')
        {
          if (!inside)
            {
              if ((i + 1) >= n)
                break;

              BUFFER[i++] = ' ';
            }

          inside = true;
          BUFFER[i++] = c;
        }
      else
        inside = false;

      c = getchar();
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
