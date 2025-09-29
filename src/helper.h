#ifndef HELPER_H
#define HELPER_H

#include "constants.h"
#include "messages.h" 
#include "types.h"

ReturnStatus add_record_to_list(Record **, Record *);
ReturnStatus sort_list_by_name(Record **);

ReturnStatus get_token_count(const char *, int *);
ReturnStatus get_next_token(const char *, char **);

#endif // HELPER_H