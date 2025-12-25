#include "types.h"

#include <stdlib.h>
#include <string.h>

InputBuffer* new_input_buffer(void) {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  if (!input_buffer) {
    return NULL;
  }

  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void close_input_buffer(InputBuffer* input_buffer) {
  if (!input_buffer) return;
  free(input_buffer->buffer);
  free(input_buffer);
}
