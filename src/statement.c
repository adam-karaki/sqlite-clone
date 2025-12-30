#include "statement.h"
#include <string.h>
#include <stdio.h>

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    int args = sscanf(
      input_buffer->buffer,
      "insert %d %s %s",
      &statement->row_to_insert.id,
      statement->row_to_insert.username,
      statement->row_to_insert.email
    );
    return (args < 3) ? PREPARE_SYNTAX_ERROR : PREPARE_SUCCESS;
  }

  if (strncmp(input_buffer->buffer, "select", 6) == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}
