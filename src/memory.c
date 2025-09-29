/**
 * @file memory.c
 * @brief Memory management functions for dynamic allocation and deallocation.
 *
 * This file contains functions for dynamically allocating and freeing memory for various structures,
 * such as 'Record' and arrays. These helper functions provide centralized memory management for the application
 * and track memory allocations for debugging or resource management purposes.
 */

// Library includes
#include <stdio.h>
#include <stdlib.h> // for malloc and free

// Code includes
#include "memory.h"

// File scope global variables
static int nStringAllocationCount = 0;
static int nArrayAllocationCount = 0;
static int nRecordAllocationCount = 0;

/**
 * @brief Dynamically allocates memory for a 'Record' structure.
 *
 * This function allocates memory for a single 'Record' structure and initializes the pointer.
 * If memory allocation fails, an error message is printed and 'FAILURE' is returned.
 *
 * @param record Pointer to the 'Record' pointer that will be allocated and initialized.
 *
 * @return SUCCESS if the memory is allocated successfully.
 *         FAILURE if memory allocation fails.
 */
ReturnStatus allocate_record_memory(Record **record)
{
    // Allocate memory for record
    *record = (Record *)malloc(sizeof(Record));
    if (*record == NULL)
    {
        printf(ERR_MEMORY_ALLOCATION_RECORD);
        return FAILURE;
    }
    nRecordAllocationCount++; // Track the number of record allocations
    return SUCCESS;
}

/**
 * @brief Frees the dynamically allocated memory for a 'Record' structure.
 *
 * This function frees the memory associated with a 'Record' structure, including the structure itself.
 * The 'record' pointer is not set to NULL after freeing, as this could cause issues if used after freeing.
 *
 * @param record Pointer to the 'Record' structure that will be freed.
 *
 * @return SUCCESS after freeing the memory.
 */
ReturnStatus clear_record_memory(Record *record)
{
    if (record != NULL)
    {
        free(record); // Free the memory allocated for the record
        nRecordAllocationCount--; // Decrement the allocation count
    }
    return SUCCESS;
}

/**
 * @brief Dynamically allocates memory for a string (character array).
 *
 * This function allocates memory for a string of a given size, including space for the null terminator.
 * If memory allocation fails, an error message is printed, and 'FAILURE' is returned.
 *
 * @param pString Pointer to the string variable that will be allocated.
 * @param size The size of the string to be allocated (excluding the null terminator).
 *
 * @return SUCCESS if the memory allocation is successful.
 *         FAILURE if memory allocation fails.
 */
ReturnStatus allocate_string_memory(char **pString, int size)
{
    *pString = malloc(size + 1); // Allocate memory for string, including space for '\0'

    if (*pString == NULL)
    {
        printf(ERR_MEMORY_ALLOCATION_STRING);
        return FAILURE;
    }

    nStringAllocationCount++; // Track the number of string allocations

    return SUCCESS;
}

/**
 * @brief Frees dynamically allocated memory for a string.
 *
 * This function frees the memory allocated for a string (character array). It checks if the string is
 * not NULL before freeing the memory to avoid errors. The pointer is not set to NULL after freeing.
 *
 * @param pString Pointer to the string whose memory needs to be freed.
 *
 * @return SUCCESS after freeing the memory.
 */
ReturnStatus clear_string_memory(char *pString)
{
    if (pString != NULL)
    {
        free(pString); // Free the allocated memory for the string
        nStringAllocationCount--; // Decrement the string allocation count
    }
    return SUCCESS;
}

/**
 * @brief Allocates memory for an integer array of the specified size.
 *
 * This function allocates memory for an array of integers based on the specified size.
 * If memory allocation fails, an error message is printed, and 'FAILURE' is returned.
 *
 * @param pArray Pointer to the integer array that will be allocated.
 * @param nSize The number of integers in the array.
 *
 * @return SUCCESS if the memory allocation is successful.
 *         FAILURE if memory allocation fails.
 */
ReturnStatus allocate_int_array_memory(int **pArray, int nSize)
{
    *pArray = (int *)malloc(nSize * sizeof(int)); // Allocate memory for the integer array

    if (*pArray == NULL)
    {
        printf(ERR_MEMORY_ALLOCATION_ARRAY);
        return FAILURE;
    }

    nArrayAllocationCount++; // Track the number of array allocations

    return SUCCESS;
}

/**
 * @brief Frees the dynamically allocated memory for an integer array.
 *
 * This function frees the memory allocated for an integer array. It checks if the pointer is not NULL
 * before attempting to free the memory, thus avoiding errors.
 *
 * @param pArray Pointer to the integer array whose memory needs to be freed.
 *
 * @return SUCCESS after freeing the memory.
 */
ReturnStatus clear_int_array_memory(int *pArray)
{
    if (pArray != NULL)
    {
        free(pArray); // Free the memory allocated for the integer array
        nArrayAllocationCount--; // Decrement the array allocation count
    }

    return SUCCESS;
}