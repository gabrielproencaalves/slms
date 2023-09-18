#include "slms.h"
#include "csv.h"
#include <stdlib.h>
#include <string.h>

extern char BUFFER[];

void add_book(CSV* db)
{
  book tmp_book_data;

  tmp_book_data.id = db->size + 1;

  tmp_book_data.title = malloc(prompt(0, "Title: ") + 1);
  strcpy(tmp_book_data.title, BUFFER);

  tmp_book_data.author = malloc(prompt(0, "Author: ") + 1);
  strcpy(tmp_book_data.author, BUFFER);

  tmp_book_data.desc = malloc(prompt(0, "Description: ") + 1);
  strcpy(tmp_book_data.desc, BUFFER);

  prompt(0, "Year: ");
  tmp_book_data.year = atoi(BUFFER);

  prompt(0, "Specimens: ");
  tmp_book_data.specimens = atoi(BUFFER);

  prompt(0, "ISBN: ");

  free(tmp_book_data.title);
  free(tmp_book_data.author);
  free(tmp_book_data.desc);
}
