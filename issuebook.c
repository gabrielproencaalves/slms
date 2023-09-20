#include "slms.h"
#include "csv.h"
#include <stdlib.h>
#include <string.h>

extern char BUFFER[];


#define getinfo(to, type) \
  to = malloc(prompt(0, type ": ") + 1); \
  strcpy(to, BUFFER)

void add_book(CSV* db)
{
  book tmp_book_data;

  tmp_book_data.id = db->size + 1;

  getinfo(tmp_book_data.title, "Title");

  getinfo(tmp_book_data.author, "Author");

  getinfo(tmp_book_data.desc, "Description");

  prompt(0, "Year: ");
  tmp_book_data.year = atoi(BUFFER);

  prompt(0, "Specimens: ");
  tmp_book_data.specimens = atoi(BUFFER);

  prompt(0, "ISBN: ");
  tmp_book_data.isbn = parse_isbn(BUFFER);

  tmp_book_data.borrows = 0;

  /* TODO: put a insertion algorithm here */
  /* oriented by book titles */

  free(tmp_book_data.title);
  free(tmp_book_data.author);
  free(tmp_book_data.desc);
  free(tmp_book_data.isbn);
}

#undef getinfo
