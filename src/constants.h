/**
 * @file constants.h
 * @brief Contains various constants and macros used throughout the program.
 *
 * This header file defines constants and macros for various parameters in the program.
 * These constants help maintain consistency and ease of maintenance by centralizing important
 * configuration values.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Return values for functions
#define OK 0     // Successful execution
#define ERROR -1 // Execution failed

// Command-line argument expectations
#define ARG_COUNT_REQUIRED 3     // Expected number of arguments
#define ARG_INDEX_PROGRAM_NAME 0 // Program name (always first argument)
#define ARG_INDEX_INPUT_FILE 1   // Input file name
#define ARG_INDEX_OUTPUT_FILE 2  // Output file output

// Default file names
#define DEFAULT_INPUT_FILE_NAME "input.txt"   // Default input file name
#define DEFAULT_OUTPUT_FILE_NAME "output.txt" // Default output file name

// String formatting constants
#define NAME_WIDTH 20 // Fixed space for the name
#define GRADE_WIDTH 5 // Fixed space for the grade
#define FILE_HEADER_STRING_FORMAT "Letter grade for %d students given in %s is:\n\n"
#define FILE_STUDENT_DATA_STRING_FORMAT "%-*s%*c\n"

// Class statistics constants
#define MINIMUM_SCORE 0
#define MAXIMUM_SCORE 100
#define ROW_AVERAGE 0
#define ROW_MINIMUM 1
#define ROW_MAXIMUM 2
#define STATS_COLUMN_WIDTH 8
#define STATS_PRECISION 2
#define DEFAULT_GRADE 'F'

// String and character constants
#define COMMA ","               // String comma for parser
#define STRING_TERMINATION '\0' // Char for string termination
#define END_OF_LINE_CHAR '\n'   // Char for end of line
#define SIZE_OF_NEW_LINE 2      // "\n\r" for Windows
#define END_OF_FILE_CHAR EOF    // Char for end of file

#endif // CONSTANTS_H
