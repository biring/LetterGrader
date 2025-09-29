/**
 * @file file.c
 * @brief Implements file handling functions for reading, writing, and processing student data files.
 *
 * This file contains utility functions to manage file input and output operations
 * for student records. The functions include opening and closing files, reading student
 * data, checking if a complete line is available for reading, and writing processed data
 * to an output file.
 */

// Library includes
#include <stdio.h>

// Code includes
#include "file.h"
#include "student.h"

/**
 * @brief Opens a file in read mode.
 *
 * This function attempts to open a specified file in read mode. If the file cannot be opened,
 * it prints an error message and returns 'FAILURE'. If the file is empty, it also returns 'FAILURE'.
 *
 * @param pFile Pointer to a 'FILE*' that will hold the file pointer upon success.
 * @param pFileName Name of the file to be opened.
 * @return SUCCESS if the file is successfully opened, otherwise FAILURE.
 */
ReturnStatus open_file_in_read_mode(FILE **pFile, const char *pFileName)
{
    // Check if the file pointer is valid
    if (*pFile != NULL)
    {
        printf(WARNING_FILE_POINTER_NOT_NULL);
    }

    // Open the file in read mode

    // If file failed to open, return failure
    *pFile = fopen(pFileName, "r");
    if (*pFile == NULL)
    {
        printf(ERR_FILE_OPEN_READ, pFileName);
        return FAILURE;
    }

    // Check if the file is empty by moving to the end and checking the size
    fseek(*pFile, 0, SEEK_END); // Move the file pointer to the end
    long size = ftell(*pFile);  // Get the current position of the file pointer (which is the file size)
    fseek(*pFile, 0, SEEK_SET); // Move the file pointer back to the beginning
    if (size == 0)
    {
        printf(ERR_FILE_EMPTY, pFileName);
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief Closes an open file.
 *
 * This function closes the given file and sets its pointer to NULL to prevent
 * dangling pointers.
 *
 * @param pFile Pointer to the 'FILE*' to be closed.
 * @return SUCCESS if the file is closed successfully, otherwise FAILURE.
 */
ReturnStatus close_file(FILE **pFile)
{
    // Check if the file pointer is NULL
    if (*pFile == NULL)
    {
        printf(WARNING_FILE_POINTER_NULL);
    }

    // Attempt to close the file
    if (fclose(*pFile) != 0)
    {
        printf("\n\nERROR! Failed to close file");
        return FAILURE;
    }

    // Set the pointer to NULL to avoid using a dangling pointer
    *pFile = NULL;

    return SUCCESS;
}

/**
 * @brief Reads a single line from a file into memory.
 *
 * Reads a line of student data from the file and stores it in a dynamically allocated
 * memory buffer.
 *
 * @param pFile Pointer to an open file.
 * @param pLineOfData Pointer to store the dynamically allocated string.
 * @param nSize Size of the line to be read.
 * @return SUCCESS if the line is read successfully, otherwise FAILURE.
 */
ReturnStatus read_one_line_from_file(FILE *pFile, char **pLineOfData, long nSize)
{
    // Read the specified number of characters from the file
    fread(*pLineOfData, sizeof(char), nSize, pFile);

    // Null-terminate the string to avoid buffer overflows
    (*pLineOfData)[nSize] = STRING_TERMINATION;

    // Move to the next line by skipping the newline character
    fseek(pFile, SIZE_OF_NEW_LINE, SEEK_CUR);

    return SUCCESS;
}

/**
 * @brief Checks if a complete line is available for reading.
 *
 * This function reads the file character by character to check if a full line
 * (terminated by a newline or EOF) is available.
 *
 * @param pFile Pointer to the file.
 * @param pIsData Pointer to a boolean indicating if data is available.
 * @param pDataSize Pointer to store the size of the available data.
 * @return SUCCESS if the operation completes successfully.
 */
ReturnStatus is_line_available_for_read(FILE *pFile, Boolean *pIsData, int *pDataSize)
{
    int ch;                        // Stores the character read from file
    long readSize = 0;             // Size of data read
    long readStart = ftell(pFile); // Store current file position

    // Read until newline or EOF
    while (TRUE)
    {
        // Read the next character from the file
        ch = getc(pFile);

        // If we encounter the end of a line
        if (ch == END_OF_LINE_CHAR)
        {
            // Calculate the size of the line (excluding the newline character)
            readSize = ftell(pFile) - SIZE_OF_NEW_LINE - readStart;
            // Exit the loop as we've found the end of the line
            break;
        }

        // If we encounter the end of file (EOF)
        if (ch == END_OF_FILE_CHAR)
        {
            // Calculate the size of the line (excluding the newline character)
            readSize = ftell(pFile) - readStart;
            // Exit the loop
            break;
        }
    }

    // Reset file pointer to initial position
    fseek(pFile, readStart, SEEK_SET);

    // Assign size and availability status
    *pDataSize = readSize;                    // Set the size of the available data (in bytes)
    *pIsData = (readSize > 0) ? TRUE : FALSE; // If data is available, set to TRUE, else FALSE

    return SUCCESS;
}

/**
 * @brief Opens a file in write mode.
 *
 * Attempts to open the file for writing. If unsuccessful, returns 'FAILURE'.
 *
 * @param pFile Pointer to a 'FILE*' that will hold the file pointer upon success.
 * @param pFileName Name of the file to be opened.
 * @return SUCCESS if the file is successfully opened, otherwise FAILURE.
 */
ReturnStatus open_file_in_write_mode(FILE **pFile, const char *pFileName)
{
    // Check if the file pointer is valid
    if (*pFile != NULL)
    {
        printf(WARNING_FILE_POINTER_NOT_NULL);
    }

    // Open the file in write mode
    *pFile = fopen(pFileName, "w");

    // If file failed to open, return failure
    if (*pFile == NULL)
    {
        printf(ERR_FILE_OPEN_WRITE, pFileName);
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief Writes the header information to the output file.
 *
 * This function writes the number of students and the input filename as metadata in the output file.
 *
 * @param pFile Pointer to the open output file.
 * @param pReadFileName Name of the original input file.
 * @return SUCCESS if the header is written successfully, otherwise FAILURE.
 */
ReturnStatus write_file_header(FILE *pFile, const char *pReadFileName)
{
    int numberOfStudents;
    int *pNumberoFStudents = &numberOfStudents;

    // Get the total number of students
    if (set_number_of_students(pNumberoFStudents) != SUCCESS)
    {
        return FAILURE;
    }

    // Write header information to the file
    fprintf(pFile, FILE_HEADER_STRING_FORMAT, numberOfStudents, pReadFileName);
    
    return SUCCESS;
}

/**
 * @brief Writes student data (names and grades) to the output file.
 *
 * @param pFile Pointer to the open output file.
 * @return SUCCESS if the data is written successfully, otherwise FAILURE.
 */
ReturnStatus write_file_data(FILE *pFile)
{
    // Delegate writing operation to another function
    if (write_names_and_grades_to_file(pFile) != SUCCESS)
    {
        return FAILURE;
    }

    return SUCCESS;
}