#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "compiler.h"

void print_prompt(void) {
  printf("db > ");
}

bool read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    return false;
  }

  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = '\0';

  return true;
}

int main(void) {
  InputBuffer* input_buffer = new_input_buffer();
  if (!input_buffer) {
    fprintf(stderr, "Failed to allocate input buffer\n");
    return EXIT_FAILURE;
  }

  while (true) {
    print_prompt();

    if (!read_input(input_buffer)) {
      break;
    }

    if (input_buffer->buffer[0] == '.') {
      if (do_meta_command(input_buffer) == META_COMMAND_SUCCESS) {
        break;
      }
      printf("Unrecognized command '%s'\n", input_buffer->buffer);
      continue;
    }

    Statement statement;
    PrepareResult result = prepare_statement(input_buffer, &statement);

    if (result == PREPARE_UNRECOGNIZED_STATEMENT) {
      printf("Unrecognized keyword at start of '%s'.\n",
             input_buffer->buffer);
      continue;
    }

    execute_statement(&statement);
    printf("Executed.\n");
  }

  close_input_buffer(input_buffer);
  return EXIT_SUCCESS;
}
