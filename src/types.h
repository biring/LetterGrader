/**
 * @file types.h
 * @brief Defines the types and structures used in the student grading program.
 *
 * This header file defines various types and structures that are used throughout the
 * program, including enumerations for status codes and boolean values, as well as
 * a student record structure for storing information about students.
 */

#ifndef TYPES_H
#define TYPES_H

// Define status codes using enum for function return
typedef enum
{
    SUCCESS = 0,  // 0 for success (standard convention)
    FAILURE = -1, // -1 for failure
} ReturnStatus;

// Define boolean values
typedef enum
{
    TRUE = 1,  // Non-zero value for true
    FALSE = 0, // 0 for false (standard convention)
} Boolean;

// Define student record structure
struct node
{
    char *name;         // Pointer to student's name
    int *scores;        // Pointer to an array of student scores
    int numberOfScores; // Number of scores in the 'scores' array
    char grade;         // Letter grade for the student
    struct node *next;  // Pointer to the next record in the list
};

// Define Record as a typedef for convenience
typedef struct node Record;

#endif // TYPES_H