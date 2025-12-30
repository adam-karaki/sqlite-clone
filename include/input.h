#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>   
#include <stdlib.h>  
#include <stddef.h>  
#include "types.h"

void read_input(InputBuffer* input_buffer);
InputBuffer* new_input_buffer(void);
void close_input_buffer(InputBuffer* input_buffer);

#endif
