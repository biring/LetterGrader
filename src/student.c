/**
 * @file student.c
 * @brief Program for processing student records, calculating grades, and generating statistical data.
 *
 * This program manages student data, including student names, test scores, and calculated grades.
 * It reads data, processes student records, computes grades based on predefined weights,
 * and calculates class statistics such as averages, minimum, and maximum scores. The program
 * also writes the student records and calculated results to a file and handles dynamic memory
 * allocation and deallocation.
 */

// Library includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Code includes
#include "helper.h"
#include "memory.h"
#include "student.h"

// Grading constants
const double TEST_WEIGHTS[] = {0.1, 0.1, 0.1, 0.1, 0.2, 0.15, 0.25}; // Weights for each test
const double GRADE_THRESHOLD[] = {90, 80, 70, 60, 0}; // Thresholds for grade calculation
const char GRADE_LETTER[] = {'A', 'B', 'C', 'D', 'F'}; // Corresponding grade letters
const char *TEST_NAMES[] = {"Quiz 1", "Quiz 2", "Quiz 3", "Quiz 4", "Mid 1", "Mid 2", "Final"}; // Test names
const char *STAT_NAMES[] = {"Average", "Minimum", "Maximum"}; // Statistical names for report

// File scope global variable
static Record *head = NULL; // Start of student record link list

// Function declaration
ReturnStatus set_name(const char *, char **, char **);
ReturnStatus set_scores(const char *, char **, int, int **);
ReturnStatus calculate_grade(Record *);
ReturnStatus calculate_average(int, double *);
ReturnStatus calculate_minimum(int, double *);
ReturnStatus calculate_maximum(int, double *);

/**
 * @brief Creates a new student record from raw data string.
 *
 * This function parses a raw data string to extract the student's name and scores,
 * and dynamically allocates memory to store the student's information.
 *
 * @param rawDataString The raw data string containing student information (name and scores).
 *
 * @return SUCCESS if the student record is created successfully.
 *         FAILURE if there is an error in creating the student record.
 */
ReturnStatus create_student(const char *rawDataString)
{
    Record *record = NULL;

    // Get the number of comma seperated fields in the string
    int nField = 0; // Track number of comma seperated fields
    if (get_token_count(rawDataString, &nField) != SUCCESS)
    {
        return FAILURE;
    }
    
    // Get student name from data string
    char *tempDataString = NULL; // Temporaty storage for string token
    char *studentName = NULL;
    if (set_name(rawDataString, &tempDataString, &studentName) != SUCCESS)
    {
        return FAILURE;
    }
    
    // Get student scores from data string
    int nScores = nField - 1; // One field for name the rest are scores
    int *studentScores = NULL;
    if (set_scores(rawDataString, &tempDataString, nScores, &studentScores) != SUCCESS)
    {
        return FAILURE;
    }
    
    // Get next token to release token memory
    if (get_next_token(rawDataString, &tempDataString) != SUCCESS)
    {
        return FAILURE;
    }

    // Dynamically allocate memory for record
    if (allocate_record_memory(&record) != SUCCESS)
    {
        return FAILURE;
    }
    
    // Update student data with name, scores and number of scores
    record->name = studentName;
    record->scores = studentScores;
    record->numberOfScores = nScores;
    record->grade = 0;
    record->next = NULL;
    
    // add student record to link list
    if (add_record_to_list(&head, record) != SUCCESS)
    {
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief Sets the name for a student from the raw data string.
 *
 * This function extracts the student's name from the raw data string and dynamically
 * allocates memory to store it.
 *
 * @param rawDataString The raw data string containing the student's name.
 * @param tempDataString Temporary storage for tokenized data.
 * @param studentName Pointer to store the dynamically allocated memory for the student's name.
 *
 * @return SUCCESS if the name is set successfully.
 *         FAILURE if there is an error setting the name.
 */
ReturnStatus set_name(const char *rawDataString, char **tempDataString, char **studentName)
{
    // Get name which is the first token
    if (get_next_token(rawDataString, tempDataString) != SUCCESS)
    {
        return FAILURE;
    }
    
    // Check name is valid
    if (tempDataString == NULL)
    {
        printf(ERR_PARSED_NAME_EMPTY);
        return FAILURE;
    }
    
    // Dynamically allocate memory for the student's name
    if (allocate_string_memory(studentName, strlen(*tempDataString)) != SUCCESS)
    {
        return FAILURE;
    }
    
    // Copy students name to dynamically allocated memory
    strncpy(*studentName, *tempDataString, strlen(*tempDataString));
    (*studentName)[strlen(*tempDataString)] = STRING_TERMINATION;
    return SUCCESS;
}

/**
 * @brief Sets the scores for a student from the raw data string.
 *
 * This function extracts and validates the scores from the raw data string and
 * stores them in dynamically allocated memory.
 *
 * @param rawDataString The raw data string containing the student's scores.
 * @param tempDataString Temporary storage for tokenized data.
 * @param nScores The number of scores to extract.
 * @param scores Pointer to store the dynamically allocated memory for the scores.
 *
 * @return SUCCESS if the scores are set successfully.
 *         FAILURE if there is an error setting the scores.
 */
ReturnStatus set_scores(const char *rawDataString, char **tempDataString, int nScores, int **scores)
{
    // Dynamically allocate memory for the student's scores
    if (allocate_int_array_memory(scores, nScores) != SUCCESS)
    {
        return FAILURE;
    }
    
    // Parse the grades
    for (int i = 0; i < nScores; i++)
    {
        // Get next score
        if (get_next_token(rawDataString, tempDataString) != SUCCESS)
        {
            return FAILURE;
        }
        *(*scores + i) = atoi(*tempDataString); // Convert string to integer
        
        // Check score is valid
        if (*(*scores + i) > MAXIMUM_SCORE || *(*scores + i) < MINIMUM_SCORE)
        {
            printf(ERR_PARSED_SCORE_INVALID, *(*scores + i), MINIMUM_SCORE, MAXIMUM_SCORE);
            return FAILURE;
        }
    }
    return SUCCESS;
}

/**
 * @brief Calculates the grades for all students.
 *
 * This function iterates through all student records and calculates their grades
 * based on the weighted scores.
 *
 * @return SUCCESS if the grades are calculated successfully for all students.
 *         FAILURE if there is an error in calculating any student's grade.
 */
ReturnStatus calculate_student_grade()
{

    Record *current = head;

    while (current != NULL)
    {

        if (calculate_grade(current) != SUCCESS)
        {
            return FAILURE;
        }
        current = current->next;
    }
    return SUCCESS;
}

/**
 * @brief Calculates the grade for a single student based on their scores.
 *
 * This function calculates the grade for a student based on weighted scores
 * and compares it with predefined grade thresholds to determine the final grade.
 *
 * @param record The student record whose grade will be calculated.
 *
 * @return SUCCESS if the grade is calculated successfully.
 *         FAILURE if there is an error in calculating the grade.
 */
ReturnStatus calculate_grade(Record *record)
{
    double sum = 0;
    int nScoresRequired = sizeof(TEST_WEIGHTS)/sizeof(double);  

    if (record->numberOfScores != nScoresRequired)
    {
        printf(ERR_INCORRECT_SCORE_COUNT, record->name, record->numberOfScores, nScoresRequired);
        return FAILURE;
    }
    
    for (int n = 0; n < record->numberOfScores; n++)
    {
        sum += (*((record->scores) + n)) * TEST_WEIGHTS[n];
    }

    for (int n = 0; n < nScoresRequired; n++)
    {
        if (sum >= GRADE_THRESHOLD[n])
        {
            record->grade = GRADE_LETTER[n];
            break;
        }
    }

    return SUCCESS;
}

/**
 * @brief Sets the total number of students in the record list.
 *
 * This function traverses the student record linked list, counting the number of student records,
 * and then stores the total count in the variable pointed to by 'nStudents'.
 *
 * @param nStudents A pointer to an integer where the total number of student records will be stored.
 *
 * @return ReturnStatus
 *         - SUCCESS (0) if the number of students is successfully counted and stored.
 *         - FAILURE (-1) if there is an error while traversing the student record list.
 *
 */

ReturnStatus set_number_of_students(int *nStudents)
{
    Record *current = head;
    int nCount = 0;

    while (current != NULL)
    {

        nCount++;
        current = current->next;
    }

    *nStudents = nCount;

    return SUCCESS;
}

/**
 * @brief Writes student names and grades to a specified file.
 *
 * This function sorts the student records by name and then iterates through each student record,
 * writing the student's name and grade to the specified file. The data is formatted according to the
 * specified width and format defined by 'FILE_STUDENT_DATA_STRING_FORMAT'.
 *
 * @param pFile A pointer to the file where the student names and grades will be written.
 *
 * @return ReturnStatus
 *         - SUCCESS (0) if the operation completes successfully.
 *         - FAILURE (-1) if there is an error during the sorting or file writing process.
 *
 */
ReturnStatus write_names_and_grades_to_file(FILE *pFile)
{
    if (sort_list_by_name(&head) != SUCCESS)
    {
        return SUCCESS;
    }

    Record *current = head;

    while (current != NULL)
    {
        fprintf(pFile, FILE_STUDENT_DATA_STRING_FORMAT, NAME_WIDTH, current->name, GRADE_WIDTH, current->grade);
        current = current->next;
    }
    return SUCCESS;
}

/**
 * @brief Displays the header for statistical output.
 *
 * This function prints the header for the statistical display, including the test names.
 *
 * @return SUCCESS if the header is displayed successfully.
 */
ReturnStatus show_header(void)
{
    printf(MSG_SHOW_AVERAGE_HEADER);

    printf("\n%*s", STATS_COLUMN_WIDTH, "");

    // Calculate the number of elements in the array
    int nColumns = sizeof(TEST_NAMES) / sizeof(TEST_NAMES[0]);

    for (int n = 0; n < nColumns; n++)
    {
        printf("%-*s", STATS_COLUMN_WIDTH, TEST_NAMES[n]);
    }

    return SUCCESS;
}

/**
 * @brief Displays the average scores for all tests.
 *
 * This function calculates and displays the average score for each test.
 *
 * @return SUCCESS if the averages are displayed successfully.
 *         FAILURE if there is an error calculating or displaying the averages.
 */
ReturnStatus show_average(void)
{
    printf("\n%-*s", STATS_COLUMN_WIDTH, STAT_NAMES[ROW_AVERAGE]);
    // Calculate the number of elements in the array
    int nColumns = sizeof(TEST_NAMES) / sizeof(TEST_NAMES[0]);

    for (int n = 0; n < nColumns; n++)
    {
        double average;

        if (calculate_average(n, &average) != SUCCESS)
        {
            return FAILURE;
        }
        printf("%-*.*f", STATS_COLUMN_WIDTH, STATS_PRECISION, average);
    }
    return SUCCESS;
}

/**
 * @brief Displays the minimum scores for all tests.
 *
 * This function calculates and displays the minimum score for each test.
 *
 * @return SUCCESS if the minimum scores are displayed successfully.
 *         FAILURE if there is an error calculating or displaying the minimums.
 */
ReturnStatus show_minimum(void)
{
    printf("\n%-*s", STATS_COLUMN_WIDTH, STAT_NAMES[ROW_MINIMUM]);
    
    // Calculate the number of elements in the array
    int nColumns = sizeof(TEST_NAMES) / sizeof(TEST_NAMES[0]);

    for (int n = 0; n < nColumns; n++)
    {
        double minimum;

        if (calculate_minimum(n, &minimum) != SUCCESS)
        {
            return FAILURE;
        }
        printf("%-*.*f", STATS_COLUMN_WIDTH, STATS_PRECISION, minimum);
    }

    return SUCCESS;
}

/**
 * @brief Displays the maximum scores for all tests.
 *
 * This function calculates and displays the maximum score for each test.
 *
 * @return SUCCESS if the maximum scores are displayed successfully.
 *         FAILURE if there is an error calculating or displaying the maximums.
 */
ReturnStatus show_maximum(void)
{
    printf("\n%-*s", STATS_COLUMN_WIDTH, STAT_NAMES[ROW_MAXIMUM]);
    // Calculate the number of elements in the array
    int nColumns = sizeof(TEST_NAMES) / sizeof(TEST_NAMES[0]);

    for (int n = 0; n < nColumns; n++)
    {
        double maximum;

        if (calculate_maximum(n, &maximum) != SUCCESS)
        {
            return FAILURE;
        }
        printf("%-*.*f", STATS_COLUMN_WIDTH, STATS_PRECISION, maximum);
    }
    return SUCCESS;
}

/**
 * @brief Calculates the average score for a specific test across all students.
 *
 * @param testNumber The test number for which the average will be calculated.
 * @param average Pointer to store the calculated average score.
 *
 * @return SUCCESS if the average is calculated successfully.
 *         FAILURE if there is an error calculating the average.
 */
ReturnStatus calculate_average(int testNumber, double *average)
{
    Record *current = head;

    double sum = 0;
    int nStudents = 0;

    while (current != NULL)
    {
        sum += *(current->scores + testNumber);
        nStudents++;
        current = current->next;
    }

    if (nStudents <= 0)
    {
        printf(ERR_DIVIDE_BY_ZERO);
        return FAILURE;
    }
    else
    {
        *average = sum / nStudents;
    }
    return SUCCESS;
}

/**
 * @brief Calculates the minimum score for a specific test across all students.
 *
 * @param testNumber The test number for which the minimum will be calculated.
 * @param minimum Pointer to store the calculated minimum score.
 *
 * @return SUCCESS if the minimum is calculated successfully.
 */
ReturnStatus calculate_minimum(int testNumber, double *minimum)
{
    Record *current = head;

    *minimum = MAXIMUM_SCORE;

    while (current != NULL)
    {
        *minimum = *minimum > *(current->scores + testNumber) ? *(current->scores + testNumber) : *minimum;
        current = current->next;
    }

    return SUCCESS;
}

/**
 * @brief Calculates the maximum score for a specific test across all students.
 *
 * @param testNumber The test number for which the maximum will be calculated.
 * @param maximum Pointer to store the calculated maximum score.
 *
 * @return SUCCESS if the maximum is calculated successfully.
 */
ReturnStatus calculate_maximum(int testNumber, double *maximum)
{
    Record *current = head;

    *maximum = MINIMUM_SCORE;

    while (current != NULL)
    {
        *maximum = *maximum < *(current->scores + testNumber) ? *(current->scores + testNumber) : *maximum;
        current = current->next;
    }

    return SUCCESS;
}

/**
 * @brief Deletes all student records and frees the allocated memory.
 *
 * This function clears the memory for all student records, including their names, scores, 
 * and the student record structures.
 *
 * @return SUCCESS if the records are deleted successfully.
 *         FAILURE if there is an error clearing any of the records.
 */
ReturnStatus delete_students(void)
{
    Record *current = head;
    Record *next = NULL;

    while (current != NULL)
    {
        next = current->next;

        if (clear_string_memory(current->name) != SUCCESS)
        {
            return FAILURE;
        }

        if (clear_int_array_memory(current->scores) != SUCCESS)
        {
            return FAILURE;
        }

        if (clear_record_memory(current) != SUCCESS)
        {
            return FAILURE;
        };

        current = next;
        head = current;
    }

    return SUCCESS;
}
