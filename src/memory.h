#ifndef MEMORY_H
#define MEMORY_H

#include "constants.h"
#include "messages.h" 
#include "types.h"

ReturnStatus allocate_record_memory(Record **);
ReturnStatus clear_record_memory(Record *);

ReturnStatus allocate_string_memory(char **, int);
ReturnStatus clear_string_memory(char *);

ReturnStatus allocate_int_array_memory(int **, int);
ReturnStatus clear_int_array_memory(int *);

#endif // MEMORY_H