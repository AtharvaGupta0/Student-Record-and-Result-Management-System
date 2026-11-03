// Library inclusion

#include <stdio.h>
#include <stdlib.h>

// Structure definition for student information

struct StudentInfo {
  int SapId;
  int RollNo;
  long long Phone;
  int Year;
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

// Functions Initialisation

void loadStudentData(void);
void addStudentRecord(void);
void saveStudentRecord(void);
void clrscreen(void);

// Main function

int main() {
  printf("Welcome to Student Record and Result Management System\n");
  loadStudentData();
  addStudentRecord();
  return 0;
}

// Function Defination



void clrscreen(void) {
  {
    printf("\033[2J\033[H");
    fflush(stdout);
  }
}


void loadStudentData(void){ 
  FILE *fp = fopen(DATA, "r");
  if (fp == NULL) {
    printf("Error opening file: %s\n", DATA);
    return;

  }
}

void addStudentRecord(void) {
  if (RecordCount >= MAX_STUDENTS) {
    printf("Maximum student records reached. Cannot add more records.\n");
    return;
  }
  printf("Enter Name of the Student: ");
  scanf("%99[^\n]", studentrecords[RecordCount].name);
  printf("Enter your Sap ID: ");
  do {
    scanf("%d", &studentrecords[RecordCount].SapId);
    if (studentrecords[RecordCount].SapId < 590000000 || studentrecords[RecordCount].SapId > 590099999) {
      printf("The Sap ID is invlaid\nRe-enter your Sap ID: ");
    }
  } while (studentrecords[RecordCount].SapId < 590000000 ||
      studentrecords[RecordCount].SapId > 590099999);
  printf("Enter your Roll No: ");
  do {
    scanf("%d", &studentrecords[RecordCount].RollNo);
    if (studentrecords[RecordCount].RollNo < 1 || studentrecords[RecordCount].RollNo > 100) {
      printf("The Roll No is invlaid\nRe-enter your Roll No: ");
    }
  } while (studentrecords[RecordCount].RollNo < 1 || studentrecords[RecordCount].RollNo > 100);
  printf("Enter your Year of Study: ");
  do {
    scanf("%d", &studentrecords[RecordCount].Year);
    if (studentrecords[RecordCount].Year < 1 || studentrecords[RecordCount].Year > 4) {
      printf("The Year of Study is invlaid\nRe-enter your Year of Study: ");
    }
  } while (studentrecords[RecordCount].Year < 1 || studentrecords[RecordCount].Year > 4);
  printf("Enter your Phone Number: ");
  do {
    scanf("%lld", &studentrecords[RecordCount].Phone);
    if (studentrecords[RecordCount].Phone < 1000000000 || studentrecords[RecordCount].Phone > 9999999999) {
      printf("The Phone Number is invlaid\nRe-enter your Phone Number: ");
    }
  } while (studentrecords[RecordCount].Phone < 1000000000 || studentrecords[RecordCount].Phone > 9999999999);
  printf("Enter your Email ID: ");
  scanf("%99s", studentrecords[RecordCount].EmailId);
  for (int i = 0; i < 8; i++) {
    printf("Enter your SGPA for Semester %d: ", i + 1);
    do {
      scanf("%f", &studentrecords[RecordCount].SGPA[i]);
      if (studentrecords[RecordCount].SGPA[i] < 0.0 || studentrecords[RecordCount].SGPA[i] > 10.0) {
        printf("The SGPA is invlaid\nRe-enter your SGPA for Semester %d: ", i + 1);
      }
    } while (studentrecords[RecordCount].SGPA[i] < 0.0 || studentrecords[RecordCount].SGPA[i] > 10.0);
    saveStudentRecord();
  }
}


void saveStudentRecord(void) {
  FILE *fp = fopen(DATA, "wb");
  if (fp == NULL) {
    printf("Error opening file: %s\n", DATA);
    return;
  }
  int saved = fwrite(studentrecords, sizeof(struct StudentInfo), RecordCount, fp);
  fclose(fp);
}