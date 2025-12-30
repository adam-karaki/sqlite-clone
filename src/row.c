#include "row.h"
#include <stdio.h>

void print_row(Row* row) {
  printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}
