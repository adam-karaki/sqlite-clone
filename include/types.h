#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <sys/types.h>

/* Input buffer */

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer(void);
void close_input_buffer(InputBuffer* input_buffer);

/* Meta commands */

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

#endif
