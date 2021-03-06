#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "Table.h"

void sage_set_root(char* r) {
  root = r;
}

Table* sage_table_open(const char *filename, size_t row_length) {
  char *path = malloc(strlen(root)+strlen(filename)+1);
  strcpy(path, root);
  strcat(path, filename);

  Table *t = malloc(sizeof(Table));

  t->row_length = row_length;
  t->file = fopen(path, "rb");

  if (t->file == NULL) {
    printf("Failed to open %s", path);
    exit(0);
  }

  free(path);
  
  return t;
}

void sage_table_close(Table *t) {
  fclose(t->file);
  free(t);
}

void* sage_table_read_next_row(Table *t) {
  if (feof(t->file)) return NULL;
  
  char *d = malloc(t->row_length);
  fread(d, 1, t->row_length, t->file);

  return d;
}
