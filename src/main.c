#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "meta.h"
#include "statement.h"
#include "execute.h"
#include "table.h"
#include "types.h"

void print_prompt(void) {
  printf("db > ");
}

int main(void) {
  InputBuffer* input_buffer = new_input_buffer();
  Table* table = new_table();

  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (input_buffer->buffer[0] == '.') {
      if (do_meta_command(input_buffer) == META_COMMAND_SUCCESS) {
        break;
      }
      printf("Unrecognized command '%s'\n", input_buffer->buffer);
      continue;
    }

    Statement statement;
    PrepareResult prep = prepare_statement(input_buffer, &statement);

    if (prep != PREPARE_SUCCESS) {
      printf("Error parsing statement.\n");
      continue;
    }

    ExecuteResult result = execute_statement(&statement, table);
    if (result == EXECUTE_TABLE_FULL) {
      printf("Error: table full.\n");
    }
  }

  close_input_buffer(input_buffer);
  free_table(table);
  return 0;
}
