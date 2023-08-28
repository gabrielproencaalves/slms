#include "file.h"
#include <stdio.h>
#include <stdlib.h>

struct book_database
{
  FILE* file;
  int size;
  int book_ptr;
};

library* file_load(const char* file_path)
{
  library* lib = malloc(sizeof(library));
  lib->file = fopen(file_path, "rb+");

  if(lib->file == NULL)
    lib->file = fopen(file_path, "wb+");

  if (fread(&lib->size, sizeof(int), 1, lib->file) == 0) {
    int zero = 0;
    fwrite(&zero, sizeof(int), 1, lib->file);
  }

  lib->book_ptr = 1;

  return lib;
}

void file_unload(library* lib)
{
  fclose(lib->file);
  free(lib);
}
