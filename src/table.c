#include "table.h"
#include <stdlib.h>
#include <string.h>

Table* new_table(void) {
  Table* table = malloc(sizeof(Table));
  table->num_rows = 0;
  for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
    table->pages[i] = NULL;
  }
  return table;
}

void free_table(Table* table) {
  for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
    free(table->pages[i]);
  }
  free(table);
}

void serialize_row(Row* source, void* destination) {
  char* dest = (char*)destination;
  memcpy(dest + ID_OFFSET, &source->id, ID_SIZE);
  memcpy(dest + USERNAME_OFFSET, source->username, USERNAME_SIZE);
  memcpy(dest + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination) {
  char* src = (char*)source;
  memcpy(&destination->id, src + ID_OFFSET, ID_SIZE);
  memcpy(destination->username, src + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(destination->email, src + EMAIL_OFFSET, EMAIL_SIZE);
}

void* row_slot(Table* table, uint32_t row_num) {
  uint32_t page_num = row_num / ROWS_PER_PAGE;
  if (table->pages[page_num] == NULL) {
    table->pages[page_num] = malloc(PAGE_SIZE);
  }

  uint32_t row_offset = row_num % ROWS_PER_PAGE;
  return (char*)table->pages[page_num] + row_offset * ROW_SIZE;
}
