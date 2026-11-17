# Student Record and Result Management System

A menu-driven console application in C for keeping student records and semester
results. It was written as a college C programming project and uses only the
standard C library.

Records are stored in a binary file, so the data is still there the next time
the program is opened.

## Features

- Add a student record with SAP ID, roll number, name, phone number, email ID,
  year, semester and SGPA for the semesters completed so far
- Search by SAP ID, or by name using a case-insensitive prefix
- Display all records
- Display all records sorted by SAP ID or by name, without changing the order
  stored in the file
- Calculate the CGPA of any student
- Calculate the average CGPA of the students in each year
- Get an academic recommendation for a student from the AI-assisted advisor
- Delete a record
- Save every change to `DataFiles/students.dat`

## Project layout

```
Student-Record-and-Result-Management-System/
├── Code/
│   └── main.c
├── DataFiles/
│   └── students.dat
├── Executables/
│   ├── Student-Record-and-Management-System      (Linux)
│   └── Student-Record-and-Management-System.exe  (Windows)
├── AI_USAGE_LOG.md
└── README.md
```

## Requirements

- A C compiler that supports C11, such as GCC, Clang, or MinGW on Windows
- No external libraries

## Building

### Linux

From the project root:

```bash
gcc -std=c11 -Wall -Wextra Code/main.c -o Executables/Student-Record-and-Management-System
```

### Windows

Using MinGW-w64, for example from the MSYS2 UCRT64 shell, run this from the
project root:

```cmd
gcc -std=c11 -Wall -Wextra Code/main.c -o Executables\Student-Record-and-Management-System.exe
```

Both builds are already included in `Executables/`, so compiling is only needed
after changing the source.

## Running

Run the program from the project root. The path to the data file is relative,
so starting it from inside `Executables/`, or by double-clicking the `.exe`,
means it cannot find `DataFiles/students.dat`.

Linux:

```bash
./Executables/Student-Record-and-Management-System
```

Windows PowerShell:

```powershell
.\Executables\Student-Record-and-Management-System.exe
```

Windows cmd:

```cmd
Executables\Student-Record-and-Management-System.exe
```

## Menu

```
========================================
 Student Record and Result Management
========================================
1. Add Student Record
2. Search Student Record
3. Display All Student Records
4. Calculate Student CGPA
5. Display Average CGPA by Year
6. Academic Advisor
7. Delete Student Record
8. Display Records Sorted by SAP ID
9. Display Records Sorted by Name
10. Exit
```

Option 2 opens a smaller search menu with SAP ID search, name search and a
return option. After an operation finishes, the program goes back to the main
menu. Invalid input is rejected and asked for again instead of ending the
program.

## AI-Assisted Academic Advisor

Option 6 asks for a SAP ID, calculates that student's CGPA from the stored SGPA
values, and prints a performance category with a short recommendation.

AI was used during development to help design the performance categories and
the recommendation wording. The final implementation is a deterministic C
function using CGPA and `if-else` statements; no AI model is executed by the
application. It needs no internet connection, API key or external service.

The categories are rules chosen for this mini project, not an official
university grading policy:

| CGPA              | Category                     | Recommendation                                                        |
|-------------------|------------------------------|-----------------------------------------------------------------------|
| 8.5 to 10.0       | Excellent Performance        | Maintain your current study pattern and consistency.                   |
| 7.0 to below 8.5  | Good Performance             | Continue your current efforts and focus on weaker subjects.            |
| 5.0 to below 7.0  | Needs Improvement            | Focus more on subjects with lower SGPA and revise regularly.           |
| Below 5.0         | Requires Immediate Attention | Strengthen fundamental concepts and seek academic support where needed. |

Example output, calculated from the stored record:

```
----------------------------------------
AI-Assisted Academic Advisor
----------------------------------------
Student: Priya Nair
SAP ID : 590000105
CGPA   : 8.80

Performance Category: Excellent Performance
Recommendation: Maintain your current study pattern and consistency.
```

The sample records in `DataFiles/students.dat` cover all four categories, so the
feature can be demonstrated without adding anything:

| Student     | SAP ID    | CGPA | Category                     |
|-------------|-----------|------|------------------------------|
| Priya Nair  | 590000105 | 8.80 | Excellent Performance        |
| Arjun Reddy | 590000110 | 7.85 | Good Performance             |
| Meera Joshi | 590000111 | 6.20 | Needs Improvement            |
| Rahul Das   | 590000112 | 4.70 | Requires Immediate Attention |

These values are calculated by the program from each student's SGPA values; no
CGPA is stored or hard-coded. See `AI_USAGE_LOG.md` for the record of AI
assistance during the project.

## Fields and validation

| Field    | Rule                                                          |
|----------|---------------------------------------------------------------|
| SAP ID   | `590000000` to `590099999`, and must be unique                |
| Roll No. | `1` to `100`                                                  |
| Name     | May contain spaces                                            |
| Phone    | 10 digits                                                     |
| Email    | Basic check for a name, `@`, and a domain with a dot          |
| Year     | `1` to `4`                                                    |
| Semester | 1–2 in first year, 3–4 in second, 5–6 in third, 7–8 in fourth |
| SGPA     | `0.0` to `10.0`                                               |

Only the semesters up to the student's current semester are asked for, and the
remaining SGPA slots are left at zero. CGPA is the average of the SGPA values
that are actually available, not the average of all eight slots.

Name search only matches from the beginning of a name, so `atha` finds
`Atharva Gupta`, but `Gupta` does not. The comparison is case-insensitive.

## About the data file

`DataFiles/students.dat` is written with `fwrite`, one fixed-size
`struct StudentInfo` per record, and read back with `fread`. It is loaded when
the program starts and rewritten after every add or delete. Up to 1000 records
are kept in memory.

The repository already contains some example records so the menu can be tried
straight away. Delete the file to start with an empty database; it is created
again on the next save.

Because the file stores the raw structure, changing the fields of
`struct StudentInfo` makes existing data files unreadable. That is acceptable
for a project of this size, but the data file has to be regenerated after such
a change.

## Sorting and searching

SAP ID search is a linear search because records are not kept in sorted order.
Name search checks the beginning of each name and continues through all
records, since names are not unique. The sorted displays use bubble sort on a
local array of pointers, so the records in memory and in the file stay in the
order they were added.

