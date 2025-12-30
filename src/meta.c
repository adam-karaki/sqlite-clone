#include "meta.h"
#include <string.h>

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    return META_COMMAND_SUCCESS;
  }
  return META_COMMAND_UNRECOGNIZED_COMMAND;
}
