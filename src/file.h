#ifndef FILE_H
#define FILE_H

#include "constants.h"
#include "messages.h" 
#include "types.h"

ReturnStatus open_file_in_read_mode(FILE **, const char *);
ReturnStatus open_file_in_write_mode(FILE **, const char *);

ReturnStatus write_file_header(FILE *pFile, const char *pReadFileName);
ReturnStatus write_file_data(FILE *pFile);

ReturnStatus is_line_available_for_read(FILE *, Boolean *, int *);
ReturnStatus read_one_line_from_file(FILE *, char **, long);

ReturnStatus close_file(FILE **pFile);

#endif // FILE_H