#ifndef SLMS_H
#define SLMS_H
#include "csv.h"

#define bool char
#define true 1
#define false 0

typedef struct _book_data {
  unsigned long int id;
  char* title;
  char* author;
  char* desc;
  int year;
  int specimens;
  int borrows;
  short* isbn;
} book ;

/*=== OUTPUT ===*/

/* initialize: set up variables */
void initialize(void);

/* newline: print a newline on panel */
int newline(void);

/* printc(c): print the character c on panel*/
int printc(char);

/* prints(s): print the string s on panel */
int prints(const char*);

/* movecur(x, y): moves the cursor to x and y */
void movecur(int, int);

/* clearc(x): clears x characters */
void clearc(int x);

/* clearl:  clears the line or x characters */
void clearl(void);

/* clear: clears the panel */
void clear(void);

/* getx: returns value of CURSOR_X */
int getx(void);

/* gety: returns value of CURSOR_Y */
int gety(void);

/* setx: sets value of CURSOR_X to x and returns it */
int setx(int);

/* sety: sets value of CURSOR_Y to x and returns it */
int sety(int);

/*=== INPUT ===*/

/* readline: reads n characters from stdin */
int readline(int);

/* prompt: prints s and reads n characters from stdin */
int prompt(int, const char*);

/*=== ISSUE BOOK ===*/

void add_book(CSV*);

/*=== CSV ===*/

/* csv_open: opens a csv file and returns a pointer to it */
CSV* csv_open(const char*);

/* csv_seek: moves file index from WHENCE to OFFSET */
int csv_seek(CSV*, int, int);

/* csv_close: frees the csv file pointer */
void csv_close(CSV*);

#endif
