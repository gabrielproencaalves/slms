#include "file.h"
#include <stdio.h>

struct book_database {
  FILE* file;
  int size;
  int book_ptr;
};
