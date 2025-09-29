#ifndef STUDENT_H
#define STUDENT_H

#include "constants.h"
#include "messages.h"
#include "types.h"

ReturnStatus create_student(const char *);
ReturnStatus delete_students();

ReturnStatus calculate_student_grade(void);
ReturnStatus set_number_of_students(int *);
ReturnStatus write_names_and_grades_to_file(FILE *pFILE);

ReturnStatus show_header(void);
ReturnStatus show_average(void);
ReturnStatus show_minimum(void);
ReturnStatus show_maximum(void);

#endif // STUDENT_H