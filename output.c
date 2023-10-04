#include <stdio.h>
#include "escapes.h"
#include "slms.h"
#include "config.h"

static int CURSOR_X;    /* Current X cursor position */
static int CURSOR_Y;    /* Current Y cursor position */
static int LAST_PRINTL; /* Last printed line         */

/* This macro moves the cursor x times to the right
   and updates the variable CURSOR_X */
#define CURSOR_FORWARD(x) \
  do                      \
    {                     \
      CUF((x));           \
      CURSOR_X += (x);    \
    }                     \
  while (0)

/* This macro moves the cursor x times to the left
   and updates the variable CURSOR_X */
#define CURSOR_BACKWARD(x) \
  do                       \
    {                      \
      CUB((x));            \
      CURSOR_X -= (x);     \
    }                      \
  while (0)

/* This macro moves the cursor up x times
   and updates the variable CURSOR_Y */
#define CURSOR_UPWARD(x)   \
  do                       \
    {                      \
      CPL((x));            \
      CURSOR_Y -= (x);     \
      CUF(CURSOR_X - 1);   \
    }                      \
  while (0)

/* This macro moves the cursor down x times
   and updates the variable CURSOR_Y */
#define CURSOR_DOWNWARD(x) \
  do                       \
    {                      \
      CNL((x));            \
      CURSOR_Y += (x);     \
      CUF(CURSOR_X - 1);   \
    }                      \
  while (0)

/* initialize: set up panel and variables */
void initialize(void)
{
  CURSOR_X = CURSOR_Y = 1;

  /* Provide the necessary height for program execution */
  for (; CURSOR_X < MAXHEIGHT + 1; CURSOR_X = ++CURSOR_Y)
    putchar('\n');

  /* Get back to initial position */
  movecur(1, 1);
}

/* newline: print a newline on panel */
int newline(void)
{
  /* If cursor is on last line */
  if (CURSOR_Y == MAXHEIGHT)
    return 0; /* Bad signal */

  CURSOR_DOWNWARD(1);  /* Move cursor down */
  CURSOR_BACKWARD(CURSOR_X - 1); /* Move cursor to first column */

  return 1; /* Good signal */
}

/* printc(c): print the character c on panel */
int printc(char c)
{
  /* If cursor reaches the margin or */
  /* the character to be printed is a newline */
  if ((CURSOR_X == MAXWIDTH + 1) || (c == '\n'))
    if (!newline() || c == '\n')
      return 0;

  /* If the new line printed is less */
  /* than the variable LAST_PRINTL */
  if (CURSOR_Y > LAST_PRINTL)
    /* Update variable LAST_PRINTL */
    LAST_PRINTL = CURSOR_Y;

  putchar(c);
  CURSOR_X++;
  return c;
}

/* prints(s): print the string s on panel */
int prints(const char *s)
{
  int i;

  /* Until reaching the end of s */
  for (i = 0; s[i] != '\0'; ++i)
    /* If chars cannot be printed */
    if (!printc(s[i]))
      return 0; /* Bad signal */

  return i; /* Return number of printed characters */
}

/* printsn(s, n): print s at maximum n characters */
int printsn(char* s, int n)
{
  int i;

  /* Until reaching the end of s and not passing the limit */
  for (i = 0; s[i] != '\0' && i < n; i++)
    /* If chars cannot be printed */
    if (!printc(s[i]))
      return 0; /* Bad signal */

  return i; /* Return number of printed characters */
}

/* movecur(x, y): moves the cursor to x and y */
void movecur(int x, int y)
{
  /* Checks if parameters extrapolate margin */
  if (x > MAXWIDTH || y > MAXHEIGHT)
    return;

  /* Just moves x if it is different of request */
  if (CURSOR_X != x)
    {
      if (CURSOR_X > x)
        CURSOR_BACKWARD(CURSOR_X - x);
      else
        CURSOR_FORWARD(x - CURSOR_X);
    }

  /* Just moves y if it is different of request */
  if (CURSOR_Y != y)
    {
      if (CURSOR_Y > y)
        CURSOR_UPWARD(CURSOR_Y - y);
      else
        CURSOR_DOWNWARD(y - CURSOR_Y);
    }
}

/* clearc(x): clears x characters */
void clearc(int x)
{
  while (x--)
    printc(' ');
}

/* clearl:  clears the line */
void clearl(void)
{
  CURSOR_BACKWARD(CURSOR_X - 1);

  /* Clears the line */
  clearc(MAXWIDTH);

  CURSOR_BACKWARD(CURSOR_X - 1);
}

/* clear: clears the panel */
void clear(void)
{
  while (CURSOR_Y > 1)
    {
      clearl();
      CURSOR_UPWARD(1);
    }

  clearl();
}

int getx(void)
{
  return CURSOR_X;
}

int gety(void)
{
  return CURSOR_Y;
}

int setx(int x)
{
  return (CURSOR_X = x);
}

int sety(int x)
{
  return (CURSOR_Y = x);
}
