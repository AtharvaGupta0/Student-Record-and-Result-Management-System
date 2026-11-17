# Student Record and Result Management System

A console-based student record and result management system written in C.

## Features

- Add student records with SAP ID, roll number, name, phone, email, year,
  semester and SGPA results
- Search by SAP ID or by name (case-insensitive prefix search)
- Delete a student record
- Display all records, or display them sorted by SAP ID or by name
- Calculate a student's CGPA and the average CGPA of each year
- Records are saved in `DataFiles/students.dat` using binary file handling

## Build and run

From the repository root:

```bash
gcc -std=c11 -Wall -Wextra Code/main.c -o Executables/Student-Record-and-Management-System
./Executables/Student-Record-and-Management-System
```

Run the program from the repository root because the data file path is
relative to the working directory.
