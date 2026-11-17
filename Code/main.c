// Library inclusion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition for student information

enum Year {
  FIRST_YEAR = 1,
  SECOND_YEAR,
  THIRD_YEAR,
  FOURTH_YEAR
};

struct StudentInfo {
  int SapId;
  int RollNo;
  enum Year Year;
  int Semester;
  long long Phone;
  float SGPA[8];
  char name[100];
  char EmailId[100];
};

// Macro definition

#define DATA "DataFiles/students.dat"
#define MAX_STUDENTS 1000

// Global Variable Declaration

struct StudentInfo studentrecords[MAX_STUDENTS];
int RecordCount = 0;

// Function declaration

void clrscreen(void);
void loadStudentData(void);
void saveStudentRecord(void);
void addStudentRecord(void);
void searchStudentRecord(void);
void searchBySapId(void);
void searchByName(void);
void displayAllRecords(void);
void displayStudent(const struct StudentInfo *student);
void displayCGPA(void);
void displayAverageCGPAByYear(void);
void deleteStudentRecord(void);
void displaySortedBySapId(void);
void displaySortedByName(void);
int findBySapId(int sapId);
float calculateCGPA(const struct StudentInfo *student);

static void discardInputLine(void);
static int readNumber(const char *prompt, long long min, long long max,
                      long long *value);
static int readFloat(const char *prompt, float min, float max, float *value);
static int readLine(const char *prompt, char *buffer, int size);
static int isValidEmail(const char *email);
static char toLowerChar(char c);
static int startsWithIgnoreCase(const char *name, const char *prefix);
static void waitForEnter(void);

// Main function

int main(void) {
  long long choice;

  loadStudentData();

  for (;;) {
    clrscreen();
    printf("========================================\n");
    printf(" Student Record and Result Management\n");
    printf("========================================\n");
    printf("1. Add Student Record\n");
    printf("2. Search Student Record\n");
    printf("3. Display All Student Records\n");
    printf("4. Calculate Student CGPA\n");
    printf("5. Display Average CGPA by Year\n");
    printf("6. Delete Student Record\n");
    printf("7. Display Records Sorted by SAP ID\n");
    printf("8. Display Records Sorted by Name\n");
    printf("9. Exit\n\n");

    if (!readNumber("Enter your choice: ", 1, 9, &choice)) {
      break;
    }
    if (choice == 9) {
      break;
    }

    switch ((int)choice) {
    case 1:
      addStudentRecord();
      break;
    case 2:
      searchStudentRecord();
      break;
    case 3:
      displayAllRecords();
      break;
    case 4:
      displayCGPA();
      break;
    case 5:
      displayAverageCGPAByYear();
      break;
    case 6:
      deleteStudentRecord();
      break;
    case 7:
      displaySortedBySapId();
      break;
    case 8:
      displaySortedByName();
      break;
    }

    waitForEnter();
  }

  printf("Exiting...\n");
  return 0;
}

// Function definition

void clrscreen(void) {
  printf("\033[2J\033[H");
  fflush(stdout);
}

/* Drops the rest of the current input line. */
static void discardInputLine(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

/* Reads a whole line and converts it to a validated number. */
static int readNumber(const char *prompt, long long min, long long max,
                      long long *value) {
  char line[100];
  char *end;
  long long number;

  for (;;) {
    printf("%s", prompt);
    if (fgets(line, sizeof line, stdin) == NULL) {
      return 0;
    }
    if (strchr(line, '\n') == NULL) {
      discardInputLine();
    }
    number = strtoll(line, &end, 10);
    if (end != line && (*end == '\n' || *end == '\0') && number >= min &&
        number <= max) {
      *value = number;
      return 1;
    }
    printf("Invalid input. Enter a number between %lld and %lld.\n", min, max);
  }
}

/* Reads a whole line and converts it to a validated decimal value. */
static int readFloat(const char *prompt, float min, float max, float *value) {
  char line[100];
  char *end;
  float number;

  for (;;) {
    printf("%s", prompt);
    if (fgets(line, sizeof line, stdin) == NULL) {
      return 0;
    }
    if (strchr(line, '\n') == NULL) {
      discardInputLine();
    }
    number = strtof(line, &end);
    if (end != line && (*end == '\n' || *end == '\0') && number >= min &&
        number <= max) {
      *value = number;
      return 1;
    }
    printf("Invalid input. Enter a value between %.1f and %.1f.\n", min, max);
  }
}

/* Reads a non-empty line of text, used for names, emails and searches. */
static int readLine(const char *prompt, char *buffer, int size) {
  for (;;) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
      return 0;
    }
    if (strchr(buffer, '\n') == NULL) {
      discardInputLine();
    } else {
      buffer[strcspn(buffer, "\n")] = '\0';
    }
    if (buffer[0] != '\0') {
      return 1;
    }
    printf("Input cannot be empty.\n");
  }
}

/* Basic check: one character before '@' and a dot with text after it. */
static int isValidEmail(const char *email) {
  const char *at = strchr(email, '@');
  const char *dot;

  if (at == NULL || at == email) {
    return 0;
  }
  dot = strchr(at, '.');
  return dot != NULL && dot != at + 1 && dot[1] != '\0';
}

/* Converts an upper-case ASCII letter to lower case. */
static char toLowerChar(char c) {
  if (c >= 'A' && c <= 'Z') {
    return (char)(c - 'A' + 'a');
  }
  return c;
}

/* Prefix comparison because name search is case-insensitive. */
static int startsWithIgnoreCase(const char *name, const char *prefix) {
  size_t length = strlen(prefix);

  if (length > strlen(name)) {
    return 0;
  }
  for (size_t i = 0; i < length; i++) {
    if (toLowerChar(name[i]) != toLowerChar(prefix[i])) {
      return 0;
    }
  }
  return 1;
}

static void waitForEnter(void) {
  char line[8];

  printf("\nPress Enter to continue...");
  fflush(stdout);
  fgets(line, sizeof line, stdin);
}

void loadStudentData(void) {
  FILE *fp = fopen(DATA, "rb");
  if (fp == NULL) {
    return; /* No data file yet: start with an empty list. */
  }
  RecordCount = (int)fread(studentrecords, sizeof(struct StudentInfo),
                           MAX_STUDENTS, fp);
  fclose(fp);
}

void saveStudentRecord(void) {
  FILE *fp = fopen(DATA, "wb");
  if (fp == NULL) {
    printf("Error opening file: %s\n", DATA);
    return;
  }
  size_t written = fwrite(studentrecords, sizeof(struct StudentInfo),
                          (size_t)RecordCount, fp);
  fclose(fp);
  if (written != (size_t)RecordCount) {
    printf("Error: only %zu of %d records were saved to %s\n", written,
           RecordCount, DATA);
  }
}

/* Returns the array index of a SAP ID, or -1 when it is not found. */
int findBySapId(int sapId) {
  for (int i = 0; i < RecordCount; i++) {
    if (studentrecords[i].SapId == sapId) {
      return i;
    }
  }
  return -1;
}

float calculateCGPA(const struct StudentInfo *student) {
  float total = 0.0f;
  int count = student->Semester;

  if (count <= 0) {
    return 0.0f;
  }
  for (int i = 0; i < count; i++) {
    total += student->SGPA[i];
  }
  return total / count;
}

void addStudentRecord(void) {
  struct StudentInfo student;
  long long value;
  int minSemester;
  int maxSemester;

  if (RecordCount >= MAX_STUDENTS) {
    printf("Maximum student records reached. Cannot add more records.\n");
    return;
  }

  /* Build the record locally so a rejected entry leaves no partial data. */
  memset(&student, 0, sizeof student);

  if (!readLine("Enter Name of the Student: ", student.name,
                sizeof student.name)) {
    return;
  }
  if (!readNumber("Enter SAP ID: ", 590000000, 590099999, &value)) {
    return;
  }
  if (findBySapId((int)value) != -1) {
    printf("A student with SAP ID %d already exists.\n", (int)value);
    return;
  }
  student.SapId = (int)value;

  if (!readNumber("Enter Roll No: ", 1, 100, &value)) {
    return;
  }
  student.RollNo = (int)value;

  if (!readNumber("Enter Year (1 to 4): ", 1, 4, &value)) {
    return;
  }
  student.Year = (enum Year)value;

  minSemester = ((int)student.Year - 1) * 2 + 1;
  maxSemester = (int)student.Year * 2;
  printf("For this year the semester must be between %d and %d.\n",
         minSemester, maxSemester);
  if (!readNumber("Enter Semester: ", minSemester, maxSemester, &value)) {
    return;
  }
  student.Semester = (int)value;

  if (!readNumber("Enter Phone Number: ", 1000000000LL, 9999999999LL, &value)) {
    return;
  }
  student.Phone = value;

  for (;;) {
    if (!readLine("Enter Email ID: ", student.EmailId,
                  sizeof student.EmailId)) {
      return;
    }
    if (isValidEmail(student.EmailId)) {
      break;
    }
    printf("Invalid email ID.\n");
  }

  /* Only semesters up to the current semester have results. */
  for (int i = 0; i < student.Semester; i++) {
    char prompt[60];
    snprintf(prompt, sizeof prompt, "Enter SGPA for Semester %d: ", i + 1);
    if (!readFloat(prompt, 0.0f, 10.0f, &student.SGPA[i])) {
      return;
    }
  }

  studentrecords[RecordCount] = student;
  RecordCount++;
  saveStudentRecord();
  printf("Student record added successfully.\n");
}

void displayStudent(const struct StudentInfo *student) {
  printf("----------------------------------------\n");
  printf("SAP ID   : %d\n", student->SapId);
  printf("Name     : %s\n", student->name);
  printf("Roll No  : %d\n", student->RollNo);
  printf("Year     : %d\n", student->Year);
  printf("Semester : %d\n", student->Semester);
  printf("Phone    : %lld\n", student->Phone);
  printf("Email    : %s\n", student->EmailId);
  printf("SGPA     : ");
  for (int i = 0; i < student->Semester; i++) {
    printf("%.2f ", student->SGPA[i]);
  }
  printf("\nCGPA     : %.2f\n", calculateCGPA(student));
}

void displayAllRecords(void) {
  if (RecordCount == 0) {
    printf("No student records found.\n");
    return;
  }
  for (int i = 0; i < RecordCount; i++) {
    displayStudent(&studentrecords[i]);
  }
  printf("Total records: %d\n", RecordCount);
}

void searchStudentRecord(void) {
  long long choice;

  printf("\n1. Search by SAP ID\n");
  printf("2. Search by Name\n");
  printf("3. Return to Main Menu\n");
  if (!readNumber("Enter your choice: ", 1, 3, &choice)) {
    return;
  }

  switch ((int)choice) {
  case 1:
    searchBySapId();
    break;
  case 2:
    searchByName();
    break;
  case 3:
    break;
  }
}

void searchBySapId(void) {
  long long value;
  int index;

  if (!readNumber("Enter SAP ID to search: ", 590000000, 590099999, &value)) {
    return;
  }
  index = findBySapId((int)value);
  if (index == -1) {
    printf("No student found with SAP ID %d.\n", (int)value);
    return;
  }
  displayStudent(&studentrecords[index]);
}

void searchByName(void) {
  char query[100];
  int matches = 0;

  if (!readLine("Enter name or beginning of name: ", query, sizeof query)) {
    return;
  }
  for (int i = 0; i < RecordCount; i++) {
    if (startsWithIgnoreCase(studentrecords[i].name, query)) {
      displayStudent(&studentrecords[i]);
      matches++;
    }
  }
  if (matches == 0) {
    printf("No matching students found.\n");
  } else {
    printf("%d matching record(s) found.\n", matches);
  }
}

void displayCGPA(void) {
  long long value;
  int index;

  if (!readNumber("Enter SAP ID: ", 590000000, 590099999, &value)) {
    return;
  }
  index = findBySapId((int)value);
  if (index == -1) {
    printf("No student found with SAP ID %d.\n", (int)value);
    return;
  }
  printf("CGPA of %s is %.2f\n", studentrecords[index].name,
         calculateCGPA(&studentrecords[index]));
}

void displayAverageCGPAByYear(void) {
  for (int year = FIRST_YEAR; year <= FOURTH_YEAR; year++) {
    float total = 0.0f;
    int count = 0;

    for (int i = 0; i < RecordCount; i++) {
      if ((int)studentrecords[i].Year == year) {
        total += calculateCGPA(&studentrecords[i]);
        count++;
      }
    }
    if (count == 0) {
      printf("Year %d: no records\n", year);
    } else {
      printf("Year %d: average CGPA = %.2f (%d student(s))\n", year,
             total / count, count);
    }
  }
}

void deleteStudentRecord(void) {
  long long value;
  int index;

  if (!readNumber("Enter SAP ID to delete: ", 590000000, 590099999, &value)) {
    return;
  }
  index = findBySapId((int)value);
  if (index == -1) {
    printf("No student found with SAP ID %d.\n", (int)value);
    return;
  }

  displayStudent(&studentrecords[index]);
  /* Shift later records left to close the gap. */
  for (int i = index; i < RecordCount - 1; i++) {
    studentrecords[i] = studentrecords[i + 1];
  }
  RecordCount--;
  saveStudentRecord();
  printf("Record deleted successfully.\n");
}

void displaySortedBySapId(void) {
  const struct StudentInfo *sorted[MAX_STUDENTS];

  if (RecordCount == 0) {
    printf("No student records found.\n");
    return;
  }
  for (int i = 0; i < RecordCount; i++) {
    sorted[i] = &studentrecords[i];
  }

  /* Sort a copy of pointers so the stored order remains unchanged. */
  for (int i = 0; i < RecordCount - 1; i++) {
    for (int j = 0; j < RecordCount - 1 - i; j++) {
      if (sorted[j]->SapId > sorted[j + 1]->SapId) {
        const struct StudentInfo *temp = sorted[j];
        sorted[j] = sorted[j + 1];
        sorted[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < RecordCount; i++) {
    displayStudent(sorted[i]);
  }
}

void displaySortedByName(void) {
  const struct StudentInfo *sorted[MAX_STUDENTS];

  if (RecordCount == 0) {
    printf("No student records found.\n");
    return;
  }
  for (int i = 0; i < RecordCount; i++) {
    sorted[i] = &studentrecords[i];
  }

  /* Sort a copy of pointers so the stored order remains unchanged. */
  for (int i = 0; i < RecordCount - 1; i++) {
    for (int j = 0; j < RecordCount - 1 - i; j++) {
      if (strcmp(sorted[j]->name, sorted[j + 1]->name) > 0) {
        const struct StudentInfo *temp = sorted[j];
        sorted[j] = sorted[j + 1];
        sorted[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < RecordCount; i++) {
    displayStudent(sorted[i]);
  }
}
