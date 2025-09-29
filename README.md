# LetterGrader

### About

*LetterGrader* is a modular C program that processes student test data, calculates final grades, and generates class-level statistics.  

The program accepts two command-line arguments:  
1. **Input file** – A CSV-formatted file containing student names and their test scores.  
2. **Output file** – A file where calculated letter grades are written in sorted order by student name.  

### Features
- **Grade Calculation**: Applies weighted scoring across quizzes, midterms, and final exam to compute each student’s overall score.  
- **Letter Assignment**: Converts numeric scores into letter grades (A–F) based on defined thresholds.  
- **Class Statistics**: Displays averages, minimums, and maximums for each test directly in the console.  
- **File I/O Support**: Reads student records from an input file and writes formatted results to an output file.  
- **Dynamic Memory Management**: Handles student records efficiently using dynamic allocation and deallocation.  
- **Linked List Implementation**: Stores student records in a linked list and sorts them alphabetically before writing results.  
- **Error Handling**: Provides feedback for invalid file access, incorrect score values, and improper arguments.  

### Technical Design
The application is organized into modular `.c` and `.h` files:  
- **`main.c`** – Main driver, orchestrates program flow.  
- **`file.c`** – File handling utilities for reading and writing student data.  
- **`student.c`** – Core student record processing, grade calculation, and statistics generation.  
- **`memory.c`** – Centralized memory management functions.  
- **`helper.c`** – Linked list operations and string token parsing.  
