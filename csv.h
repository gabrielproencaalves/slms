#ifndef CSV_H
#define CSV_H
#include "stdio.h"
#define MAX_HEADERS_NUM 7

typedef struct csv_file
{
  FILE* file;
  char* headers[MAX_HEADERS_NUM];
  int n_headers;
  unsigned long int line;
  long size;
} CSV;

#endif
