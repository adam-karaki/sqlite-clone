#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "meta.h"
#include "statement.h"
#include "execute.h"
#include "table.h"
#include "types.h"
#include "input.h"

void print_prompt(void) {
  printf("db > ");
}

int main(void) {
  InputBuffer* input_buffer = new_input_buffer();
  Table* table = new_table();

  while (true) {
    print_prompt();
    read_input(input_buffer);

    /* Meta commands */
    if (input_buffer->buffer[0] == '.') {
      if (do_meta_command(input_buffer) == META_COMMAND_SUCCESS) {
        break;
      }
      printf("Unrecognized command '%s'\n", input_buffer->buffer);
      continue;
    }

    Statement statement;
    PrepareResult prep = prepare_statement(input_buffer, &statement);

    /* Handle prepare errors */
    switch (prep) {
      case PREPARE_SUCCESS:
        break;

      case PREPARE_NEGATIVE_ID:
        printf("ID must be positive.\n");
        continue;

      case PREPARE_STRING_TOO_LONG:
        printf("String is too long.\n");
        continue;

      case PREPARE_SYNTAX_ERROR:
        printf("Syntax error. Could not parse statement.\n");
        continue;

      case PREPARE_UNRECOGNIZED_STATEMENT:
        printf("Unrecognized keyword at start of '%s'.\n",
               input_buffer->buffer);
        continue;
    }

    /* Execute statement */
    ExecuteResult result = execute_statement(&statement, table);

    switch (result) {
      case EXECUTE_SUCCESS:
        printf("Executed.\n");
        break;

      case EXECUTE_TABLE_FULL:
        printf("Error: Table full.\n");
        break;
    }
  }

  close_input_buffer(input_buffer);
  free_table(table);
  return 0;
}
