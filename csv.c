#include "csv.h"
#include <stdio.h>
#include <stdlib.h>

CSV* csv_open(const char* path)
{
  CSV* csv = malloc(sizeof(CSV));

  csv.file = fopen(path, "r+");

  if (csv.file = NULL)
    csv.file = fopen(path, "w+");

  /* if the file is empty, i.e., never used then */
  if (ungetc(fgetc(csv.file), csv.file) == EOF) {

    /* insert the headers in the file */
    fputs(csv.file, "title,author,desc,year,specimens,borrows,isbn\n");

    /* copy the headers information to csv struct */
    /* for later uses */
    csv.headers[0] = malloc(6);
    strcpy(csv.headers[0], "title");

    csv.headers[1] = malloc(7);
    strcpy(csv.headers[1], "author");

    csv.headers[2] = malloc(5);
    strcpy(csv.headers[2], "desc");

    csv.headers[3] = malloc(5);
    strcpy(csv.headers[3], "year");

    csv.headers[4] = malloc(10);
    strcpy(csv.headers[4], "specimens");

    csv.headers[5] = malloc(8);
    strcpy(csv.headers[5], "borrows");

    csv.headers[6] = malloc(5);
    strcpy(csv.headers[6], "isbn");

    csv.n_headers = 7;
  }

  else {
    int c;
    char* tmp;
    char buffer[BUFSIZ] = "";

    /* while blank spaces, next character  */
    while ((c=fgetc(csv.file)) == ' ' || c == '\n');
    /* push c back to file */
    ungetc(c, csv.file);

    fgets(buffer, BUFSIZ, csv.file);

    tmp = strtok(BUFFER, ",");
    csv.headers[0] = malloc(strlen(tmp) + 1);
    strcpy(csv.headers[0], tmp);

    for (c = 1; tmp && c < MAX_HEADERS_NUM; c++) {
      tmp = strtok(NULL, ",");
      csv.headers[c] = malloc(strlen(tmp) + 1);
      strcpy(csv.headers[c], tmp);
    }

    { /* remove the final '\n' character from csv.headers[c] */
      int last_header_size = strlen(csv.headers[c]);
      tmp = csv.headers[c];

      csv.headers[c] = realloc(csv.headers[c], last_header_size));

      if (csv.headers[c])
        csv.headers[c][last_header_size - 1] = '\0';
      else
        csv.headers[c] = tmp;
    }

    csv.n_headers = c + 1;
  }

  csv.line = 1;

  return csv;
}

void csv_close(CSV* csv)
{
  int n;

  for (n = 0; csv.headers[n] && n < MAX_HEADERS_NUM; n++)
    free(csv.headers[n]);

  fclose(csv.file);
  free(csv);
}
