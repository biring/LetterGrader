/**
 * @file main.c
 * @brief Program for processing student data, calculating grades, and generating class statistics.
 *
 * This program reads student information from an input file, processes the data,
 * calculates grades, and writes the results to an output file. It also generates
 * and displays statistical insights such as average, minimum, and maximum scores.
 *
 * Features:
 * - Reads student data from a specified input file.
 * - Parses and processes student records.
 * - Computes student grades based on provided scores.
 * - Writes processed student data to an output file.
 * - Displays class statistics including average, minimum, and maximum scores.
 * - Implements dynamic memory management for handling student records.
 *
 * Usage:
 * - The program expects command-line arguments specifying the input and output file names.
 * - If incorrect arguments are provided, default file names are used.
 * - The program follows a structured approach using modular functions.
 *
 * Return Codes:
 * - SUCCESS (0): The program executed successfully.
 * - FAILURE (-1): An error occurred during execution.
 */

// Library includes
#include <stdio.h>

// Code includes
#include "constants.h"
#include "file.h"
#include "memory.h"
#include "messages.h"
#include "student.h"
#include "types.h"

// Function declaration
ReturnStatus process_args(int, char **, char **, char **);
ReturnStatus read_student_data(const char *);
ReturnStatus process_student_data(FILE *);
ReturnStatus write_student_data(const char *, const char *);
ReturnStatus show_class_statistics(void);
ReturnStatus clear_dynamic_memmory(void);

/**
 * @brief Main function to execute the student data processing program.
 *
 * This function initializes the program, processes command-line arguments,
 * reads student data, computes grades, writes processed data to an output file,
 * displays class statistics, and clears dynamically allocated memory.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return SUCCESS if the program executes successfully, otherwise FAILURE.
 */
int main(int argc, char *argv[])
{
    ReturnStatus status = SUCCESS;
    char *pReadFileName = NULL;
    char *pWriteFileName = NULL;

    // Display the welcome message
    printf(MSG_WELCOME);

    do
    {
        // Process the command line arguments
        if (process_args(argc, argv, &pReadFileName, &pWriteFileName) != SUCCESS)
        {
            status = FAILURE;
            break;
        }

        // Read and process student data from input file
        if (read_student_data(pReadFileName) != SUCCESS)
        {
            status = FAILURE;
            break;
        }

        // Write processed student data to output file
        if (write_student_data(pReadFileName, pWriteFileName) != SUCCESS)
        {
            status = FAILURE;
            break;
        }

        // Show class statistics
        if (show_class_statistics() != SUCCESS)
        {
            status = FAILURE;
            break;
        }

        // Clear dynamically allocated memeory
        if (clear_dynamic_memmory() != SUCCESS)
        {
            status = FAILURE;
            break;
        }
    } while (FALSE); // This loop runs only once, allowing for an easy break if any step fails

    // Wait for the user to press Enter before exiting the program
    printf(PROMPT_FOR_ENTER_TO_EXIT);
    getchar(); // Ensures the user acknowledges the program before it terminates

    return status;
}

/**
 * @brief Processes command-line arguments to extract input and output file names.
 *
 * If the correct number of arguments is provided, it assigns the file names from the arguments.
 * Otherwise, it assigns default file names and displays a warning message.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @param pReadFileName Pointer to store the extracted or default input file name.
 * @param pWriteFileName Pointer to store the extracted or default output file name.
 * @return SUCCESS if arguments are processed successfully, otherwise FAILURE.
 */
ReturnStatus process_args(int argc, char **argv, char **pReadFileName, char **pWriteFileName)
{
    // Check if the argument count matches the expected value
    if (argc != ARG_COUNT_REQUIRED)
    {
        printf(WARNING_INVALID_ARGUMENT_COUNT);
        printf(MSG_INVALID_ARGUMENT_COUNT);
        // Assign default file names if arguments are incorrect
        *pReadFileName = DEFAULT_INPUT_FILE_NAME;
        *pWriteFileName = DEFAULT_OUTPUT_FILE_NAME;
    }
    else
    {
        // Assign file names from command-line arguments
        printf(MSG_VALID_ARGUMENT_COUNT);
        *pReadFileName = argv[ARG_INDEX_INPUT_FILE];
        *pWriteFileName = argv[ARG_INDEX_OUTPUT_FILE];
    }
    // UI message with selected file names
    // printf(MSG_READ_FROM_INPUT_FILE, *pReadFileName);
    // printf(MSG_WRITE_TO_OUTPUT_FILE, *pWriteFileName);
    return SUCCESS;
}

/**
 * @brief Reads student data from a specified file and processes it.
 *
 * Opens the file in read mode, extracts student records, processes them, and calculates grades.
 * Closes the file after processing.
 *
 * @param pReadFileName The name of the file containing student data.
 * @return SUCCESS if data is read and processed successfully, otherwise FAILURE.
 */
ReturnStatus read_student_data(const char *pReadFileName)
{
    FILE *pFile = NULL;

    // Open the input file for reading
    if (open_file_in_read_mode(&pFile, pReadFileName) != SUCCESS)
    {
        return FAILURE;
    }

    printf(MSG_STUDENT_DATA_READ_DONE, pReadFileName);

    // Process student data
    if (process_student_data(pFile) != SUCCESS)
    {
        close_file(&pFile);
        return FAILURE;
    }

    // Calculate grades after processing student data
    if (calculate_student_grade() != SUCCESS)
    {
        close_file(&pFile);
        return FAILURE;
    }

    printf(MSG_STUDENT_GRADING_DONE);

    // Close the file after processing
    close_file(&pFile);

    return SUCCESS;
}

/**
 * @brief Processes student data from an open file.
 *
 * Reads each line of the file, extracts student information, and stores it in a linked list.
 * Performs memory allocation for data storage.
 *
 * @param pFile Pointer to an open file in read mode.
 * @return SUCCESS if the student data is processed correctly, otherwise FAILURE.
 */
ReturnStatus process_student_data(FILE *pFile)
{
    Boolean IsLine = FALSE;  // To track if a line of student data is available. Set to FALSE initially
    int DataSize = 0;        // Size of data to be allocated
    char *DataString = NULL; // Pointer to store the data string

    // Check if a line is available to read and set pIsData and pDataSize
    if (is_line_available_for_read(pFile, &IsLine, &DataSize) != SUCCESS)
    {
        return FAILURE;
    }

    // Process while there is data to read
    while (IsLine == TRUE)
    {
        // Allocate memory for the string based on pDataSize
        if (allocate_string_memory(&DataString, DataSize) != SUCCESS)
        {
            return FAILURE;
        }

        // Read the next line from the file into pDataString
        if (read_one_line_from_file(pFile, &DataString, DataSize) != SUCCESS)
        {
            return FAILURE;
        }

        // Optionally process the data here (e.g., storing student data)
        if (create_student(DataString) != SUCCESS)
        {
            return FAILURE;
        }

        // Clear the allocated memory after use
        clear_string_memory(DataString);

        // Check if another line is available
        if (is_line_available_for_read(pFile, &IsLine, &DataSize) != SUCCESS)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}

/**
 * @brief Writes processed student data to an output file.
 *
 * Opens the specified file in write mode, writes a header, and saves the student data.
 * Closes the file after writing.
 *
 * @param pReadFileName The original input file name (for reference in output).
 * @param pWriteFileName The name of the file where processed student data is stored.
 * @return SUCCESS if data is written successfully, otherwise FAILURE.
 */
ReturnStatus write_student_data(const char *pReadFileName, const char *pWriteFileName)
{
    FILE *pFile = NULL;

    // Open the output file for writing
    if (open_file_in_write_mode(&pFile, pWriteFileName) != SUCCESS)
    {
        return FAILURE;
    }

    // Write a header with file metadata
    if (write_file_header(pFile, pReadFileName) != SUCCESS)
    {
        close_file(&pFile);
        return FAILURE;
    }

    // Write student data to the file
    if (write_file_data(pFile) != SUCCESS)
    {
        close_file(&pFile);
        return FAILURE;
    }

    // Close the output file
    close_file(&pFile);

    printf(MSG_STUDENT_GRADE_WRITE_DONE, pWriteFileName);

    return SUCCESS;
}

/**
 * @brief Displays class statistics including average, minimum, and maximum scores.
 *
 * Computes and presents statistical insights from the processed student data.
 *
 * @return SUCCESS if statistics are displayed correctly, otherwise FAILURE.
 */
ReturnStatus show_class_statistics(void)
{
    // Display the class statistics header
    if (show_header() != SUCCESS)
    {
        return FAILURE;
    }

    // Show average score
    if (show_average() != SUCCESS)
    {
        return FAILURE;
    }

    // Show minimum score
    if (show_minimum() != SUCCESS)
    {
        return FAILURE;
    }

    // Show maximum score
    if (show_maximum() != SUCCESS)
    {
        return FAILURE;
    }

    return SUCCESS;
};

/**
 * @brief Frees dynamically allocated memory used for student data storage.
 *
 * Clears all allocated memory to prevent memory leaks.
 *
 * @return SUCCESS if memory is cleared successfully, otherwise FAILURE.
 */
ReturnStatus clear_dynamic_memmory(void)
{
    // Delete student records from memory
    if (delete_students() != SUCCESS)
    {
        return FAILURE;
    }
    return SUCCESS;
};