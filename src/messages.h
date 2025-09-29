/**
 * @file messages.h
 * @brief Defines various messages used for informational, warning, and error outputs in the program.
 *
 * This header file contains a set of message constants that are used throughout the program to
 * display informational prompts, warnings, and error messages. These messages help provide feedback
 * to the user about the application's status, as well as assist in debugging and handling edge cases.
 */

#ifndef MESSAGES_H
#define MESSAGES_H

// Prompts
#define PROMPT_FOR_ENTER_TO_EXIT "\n\nPress enter to exit..."

// Informational Messages
#define MSG_WELCOME "Welcome to the Letter Grader application"
#define MSG_INVALID_ARGUMENT_COUNT "\nApplication will use default read and write file names!"
#define MSG_VALID_ARGUMENT_COUNT "\n\nApplication will use read and write files names provided in the command line arguments"
#define MSG_READ_FROM_INPUT_FILE "\n\nInput will be read from '%s'"
#define MSG_WRITE_TO_OUTPUT_FILE "\nOutput will be written to '%s'"
#define MSG_STUDENT_DATA_READ_DONE "\n\nStudent data read from input file '%s'"
#define MSG_STUDENT_GRADING_DONE "\nLetter grade has been calculated for all stuudents"
#define MSG_STUDENT_GRADE_WRITE_DONE "\nStudent letter grades written to output file '%s'"
#define MSG_SHOW_AVERAGE_HEADER "\n\nHere is the class averages:"

// Warnings
#define WARNING_INVALID_ARGUMENT_COUNT "\n\nWARNING! Command line argument format not suppoprted."
#define WARNING_FILE_POINTER_NOT_NULL "\nWARNING! File pointer is not NULL"
#define WARNING_FILE_POINTER_NULL "\nWARNING! File pointer is NULL"
#define WARNING_PARSED_DATA_EMPTY "\nWARNING! Parsed data is empty"

// Errors
#define ERR_FILE_OPEN_READ "\n\nERROR! Failed to open '%s' file for read operation"
#define ERR_FILE_OPEN_WRITE "\n\nERROR! Failed to open '%s' file for write operation"
#define ERR_FILE_EMPTY "\n\nERROR! File '%s' is empty"
#define ERR_FILE_CLOSE "\n\nERROR! Failed to close '%s' file"
#define ERR_MEMORY_ALLOCATION_STRING "\n\nERROR! Failed to allocate memory for string"
#define ERR_MEMORY_ALLOCATION_ARRAY "\n\nERROR! Failed to allocate memory for array"
#define ERR_MEMORY_ALLOCATION_RECORD "\n\nERROR! Failed to allocate memory for record data structure"
#define ERR_PARSED_NAME_EMPTY "\n\nERROR! Parsed name is empty"
#define ERR_PARSED_SCORE_INVALID "\n\nERROR! Parsed score '%d' is not within score range of '%d' to '%d'"
#define ERR_INCORRECT_SCORE_COUNT "\n\nERROR! Student %s has %d scores, %d scores are required to calculate the grade"
#define ERR_RECORD_EMPTY "\n\nERROR! Student record for link list operation is empty"
#define ERR_DIVIDE_BY_ZERO "\n\nERROR! Divide by zero attempted"

#endif // MESSAGES_H