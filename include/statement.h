#ifndef STATEMENT_H
#define STATEMENT_H

#include "row.h"
#include "types.h"

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

#endif
