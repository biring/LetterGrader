/**
 * @file helper.c
 * @brief General helper functions for linked list operations and token handling.
 *
 * This file contains helper functions for managing linked lists, adding and sorting records, and
 * handling tokenization of strings. The functions provide utility for creating and manipulating
 * linked lists of records, as well as parsing and processing comma-separated tokenized data.
 */

// Library includes
#include <stdio.h>
#include <string.h>

// Code includes
#include "helper.h"
#include "memory.h"

// Function declaration
ReturnStatus new_record_list(Record **, Record *);
ReturnStatus append_record_list(Record *, Record *);

/**
 * @brief Adds a record to the linked list.
 *
 * This function checks if the list is empty and either creates a new list or appends
 * the record to the end of the list. It handles the insertion of the record appropriately
 * based on the current state of the linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @param record Pointer to the record to be added.
 *
 * @return SUCCESS if the record is successfully added.
 *         FAILURE if an error occurs during the process.
 */
ReturnStatus add_record_to_list(Record **head, Record *record)
{
    // Record must not be NULL
    if (record == NULL)
    {
        printf(ERR_RECORD_EMPTY);
        return FAILURE;
    }

    // If the list is empty, create a new record list
    if (*head == NULL)
    {
        if (new_record_list(head, record) != SUCCESS)
        {
            return FAILURE;
        }
    }
    else
    {
        Record *last = *head;
        // Traverse to the last node
        while (last->next != NULL)
        {
            last = last->next;
        }
        // Append the record to the end of the list
        if (append_record_list(last, record) != SUCCESS)
        {
            return FAILURE;
        };
    }
    return SUCCESS;
}

/**
 * @brief Sorts the linked list by the name field.
 *
 * This function performs a bubble sort on the linked list, comparing the 'name' fields
 * of the records. If the names are out of order, the nodes are swapped to sort the list.
 *
 * @param head Pointer to the head of the linked list.
 *
 * @return SUCCESS if the list is successfully sorted.
 *         FAILURE if an error occurs during sorting.
 */
ReturnStatus sort_list_by_name(Record **head)
{
    // Don't attempt to sort an empty list
    if (*head == NULL)
    {
        printf(ERR_RECORD_EMPTY);
        return FAILURE;
    }

    // No sort needed if there is only one node
    if ((*head)->next == NULL)
    {
        return SUCCESS;
    }

    Boolean isSwap = TRUE;
    Record *previous = NULL;
    Record *current = NULL;
    Record *next = NULL;
    //Record *temp = NULL;

    // Continue sorting as long as a swap was made in the previous pass
    while (isSwap)
    {
        isSwap = FALSE;
        current = *head; // Reset current to head at the start of each pass
        previous = NULL;

        // Traverse the list and perform swaps if needed
        while (current->next != NULL)
        {
            next = current->next;

            // Compare names and swap nodes if needed
            if (strcmp(current->name, next->name) > 0)
            {
                // Perform swap of nodes
                isSwap = TRUE; // Mark that we swapped
                // Redirect previos nodes
                if (previous == NULL) // If current is the head node
                {
                    // Update head to the next node
                    *head = next;
                }
                else
                {
                    previous->next = next;
                }
                // Perform the node swap
                current->next = next->next;
                next->next = current;
                previous = next;
            }
            else
            {
                // Move to the next node in the list if no swap occurred
                previous = current;
                current = current->next;
            }
        }
    }
    return SUCCESS;
}

/**
 * @brief Initializes a new linked list with a single record.
 *
 * This function sets the head of the linked list to point to the provided record
 * and sets the record's next pointer to NULL, indicating it is the only node in the list.
 *
 * @param head Pointer to the head of the linked list.
 * @param record The record to initialize the list with.
 *
 * @return SUCCESS if the list is successfully initialized.
 */
ReturnStatus new_record_list(Record **head, Record *record)
{
    record->next = NULL;
    *head = record;
    return SUCCESS;
}

/**
 * @brief Appends a record to the end of the linked list.
 *
 * This function appends the provided record to the end of the existing list by
 * setting the next pointer of the last node to the new record.
 *
 * @param last Pointer to the last record in the list.
 * @param record The record to append.
 *
 * @return SUCCESS if the record is successfully appended.
 */
ReturnStatus append_record_list(Record *last, Record *record)
{
    record->next = NULL;
    last->next = record;
    return SUCCESS;
}

/**
 * @brief Counts the number of tokens in a CSV string.
 *
 * This function uses 'strtok' to tokenize the input string by commas and counts
 * the number of resulting tokens. It creates a copy of the input string to prevent
 * modification of the original string.
 *
 * @param pString The input CSV string.
 * @param ntokens Pointer to an integer that will store the number of tokens.
 *
 * @return SUCCESS if the token count is successfully calculated.
 *         FAILURE if memory allocation fails for copying the string.
 */
ReturnStatus get_token_count(const char *pString, int *ntokens)
{
    char *pTemp = NULL; // To create a copy of string as strtok will modify the string

    // Allocate memory for a copy of input string becasue strtok will modify the string
    if (allocate_string_memory(&pTemp, strlen(pString)) != SUCCESS)
    {
        return FAILURE;
    }

    // Copy the string into the allocated memory
    strcpy(pTemp, pString);

    // Tokenize the string by commas
    char *token = strtok(pTemp, COMMA);

    *ntokens = 0;

    while (token != NULL)
    {
        (*ntokens)++;                // Increment the token counter
        token = strtok(NULL, COMMA); // Get the next token
    }

    // Free the allocated memory
    clear_string_memory(pTemp);

    return SUCCESS;
}

/**
 * @brief Retrieves the next token in a CSV string.
 *
 * This function retrieves the next token from a CSV string using 'strtok'.
 * It uses a static pointer to remember the position in the string for subsequent calls.
 *
 * @param string The input CSV string.
 * @param token Pointer to a string where the next token will be stored.
 *
 * @return SUCCESS if the next token is successfully retrieved.
 *         FAILURE if memory allocation fails for copying the string.
 */
ReturnStatus get_next_token(const char *string, char **token)
{
    static char *temp = NULL;
    if (*token == NULL)
    {
        // Allocate memory for a copy of input string becasue strtok will modify the string
        if (allocate_string_memory(&temp, strlen(string)) != SUCCESS)
        {
            return FAILURE;
        }
        // Copy the string into the allocated memory
        strcpy(temp, string);
        // Tokenize the string by commas
        *token = strtok(temp, COMMA);
        return SUCCESS;
    }
    *token = strtok(NULL, COMMA); // Get the next token

    if (*token == NULL)
    {
        // Free the allocated memory
        clear_string_memory(temp);
        temp = NULL;
    }

    return SUCCESS;
}
