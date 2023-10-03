#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _goto_start_of_line(FILE* file)
{  while(fgetc(file) != '\n')
    fseek(file, -2, SEEK_CUR);
}

CSV* csv_open(const char* path)
{

  CSV* csv = malloc(sizeof(CSV));
  csv->file = fopen(path, "r+");
  csv->size = 0;

  if (csv->file == NULL)
    csv->file = fopen(path, "w+");

  /* if the file is empty, i.e., never used then */
  if (ungetc(fgetc(csv->file), csv->file) == EOF) {

    /* insert the headers in the file */
    fputs("title,author,desc,year,specimens,borrows,isbn\n", csv->file);

    /* copy the headers information to csv struct */
    /* for later uses */
    csv->headers[0] = malloc(6);
    strcpy(csv->headers[0], "title");

    csv->headers[1] = malloc(7);
    strcpy(csv->headers[1], "author");

    csv->headers[2] = malloc(5);
    strcpy(csv->headers[2], "desc");

    csv->headers[3] = malloc(5);
    strcpy(csv->headers[3], "year");

    csv->headers[4] = malloc(10);
    strcpy(csv->headers[4], "specimens");

    csv->headers[5] = malloc(8);
    strcpy(csv->headers[5], "borrows");

    csv->headers[6] = malloc(5);
    strcpy(csv->headers[6], "isbn");

    csv->n_headers = 7;
  }

  else {
    int c;
    char* tmp;
    char buffer[BUFSIZ] = "";

    fgets(buffer, BUFSIZ, csv->file);

    tmp = strtok(buffer, ",");
    csv->headers[0] = malloc(strlen(tmp) + 1);
    strcpy(csv->headers[0], tmp);

    for (c = 1; tmp && c < MAX_HEADERS_NUM; c++) {
      tmp = strtok(NULL, ",");
      csv->headers[c] = malloc(strlen(tmp) + 1);
      strcpy(csv->headers[c], tmp);
    }

    --c;

    {
      /* remove the final '\n' character from csv->headers[c] */
      int last_header_size = strlen(csv->headers[c]);
      tmp = csv->headers[c];

      csv->headers[c] = realloc(csv->headers[c], last_header_size);

      if (csv->headers[c])
        csv->headers[c][last_header_size - 1] = '\0';
      else
        csv->headers[c] = tmp;
    }

    csv->n_headers = c + 1;

    while ((c=fgetc(csv->file)) != EOF)
      if (c == '\n')
        csv->size++;

    fseek(csv->file, 0, SEEK_SET);

    while (fgetc(csv->file) != '\n');
  }

  csv->line = 1;

  return csv;
}

int csv_write(CSV* csv, char** s_list)
{
  int n;
  int len = (sizeof(s_list)/sizeof(s_list[0]));

  fputs(s_list[0]);
  for (n = 1; n < len; ++n) {
    fputc(',');
    fputs(s_list[n]);
  }
  fputc('\n');
  csv.line++;

  return n + 1;
}

int csv_seek(CSV* csv, int offset, int whence)
{
  int c;

  if (csv == NULL)
    return 0;

  switch (whence)
  {
    case SEEK_SET:
      /* if already on first line then
         just go to the start of line */

      if (csv->line == 1) {
        fseek(csv->file, -1, SEEK_CUR);
        _goto_start_of_line(csv->file);
        break;
      }

      /* else, goto the first line */
      while (csv->line > 1) {
        fseek(csv->file, -2, SEEK_CUR);
        _goto_start_of_line(csv->file);
        csv->line--;
      }
      break;

    case SEEK_END:
    {
      while ((c=fgetc(csv->file)) != EOF)
        if (c == '\n')
          csv->line++;

      fseek(csv->file, -2, SEEK_CUR);
      _goto_start_of_line(csv->file);
      csv->line--;
      break;
    }
  }

  if (offset != 0 && (offset + csv->line) > 0) {
    int n = offset;

    if (offset < 0) {
      while (n++ != 0) {
        fseek(csv->file, -2, SEEK_CUR);
        _goto_start_of_line(csv->file);
        csv->line--;
      }

      return offset;
    }

    while (n-- != 0) {
      while ((c=fgetc(csv->file)) != EOF) {
        if (c == '\n') {
          csv->line++;
          break;
        }
      }
    }
  }

  return offset;
}

void csv_close(CSV* csv)
{
  int n;

  for (n = 0; csv->headers[n] && n < MAX_HEADERS_NUM; n++)
    free(csv->headers[n]);

  fclose(csv->file);
  free(csv);
}
