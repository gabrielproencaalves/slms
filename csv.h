#ifndef CSV_H
#define CSV_H
#include "stdio.h"
#define MAX_HEADERS_NUM 7

typedef struct csv_file {
  FILE* file;
  char* headers[MAX_HEADERS_NUM];
  int n_headers;
  unsigned long int line;
  long size;
} CSV;

/* csv_open: opens a csv file and returns a pointer to it */
CSV* csv_open(const char*);

/* csv_seek: moves file index from WHENCE to OFFSET */
int csv_seek(CSV*, int, int);

/* csv_write: writes n string's to csv file */
int csv_write(CSV*, char**, int);

/* csv_close: frees the csv file pointer */
void csv_close(CSV*);

#endif
