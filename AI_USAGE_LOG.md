# AI Usage Log

This project was developed with some help from AI tools. This log records what
they were used for, as required by the assignment.

## 1. Designing the academic advisor rules

**AI tool used:** ChatGPT

**Purpose:** To help design the academic performance categories and suitable
study recommendations based on a student's CGPA on a 10-point scale.

**Prompt / question:**

> Suggest simple academic performance categories and corresponding study
> advice based on a student's CGPA on a 10-point scale. The categories will be
> implemented using if-else statements in a C student record management
> project.

**Useful idea obtained:** The suggestion was to divide students into CGPA
ranges and pair each range with one short piece of academic advice.

**Review / modification:** The suggestion was reviewed before it was used in
the project. The number of categories was kept at four, the boundaries were
fixed at 8.5, 7.0 and 5.0, and the advice was shortened so that it fits on one
line in the console. These are rules chosen for this mini project, not an
official university grading policy. The rules were written by hand as
if-else statements in `Code/main.c`. The running program does not contact
ChatGPT or any other AI service.

## 2. Coding assistance during development

**AI tool used:** DeepSeek (coding assistant in the development environment)

**Purpose:** General help with the C implementation: the menu structure, the
binary file load and save functions, the search and sort functions, and the
academic advisor function. It was also used while compiling and testing the
program.

**How the suggestions were used:** Suggested code was reviewed, adapted to the
existing style of the project, and tested locally before being kept.
Compilation was checked with `-Wall -Wextra -Wpedantic`, and the menu
operations were tested with scripted input.

**What the program does not do:** It does not call DeepSeek, ChatGPT, any AI
API, or any network service at runtime. All recommendations are produced by
ordinary C if-else statements.
