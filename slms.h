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

#endif /* SLMS_H */
