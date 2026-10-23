// Library inclusion

#include <stdio.h>

// Structure definition for student information

struct StudentInfo {
  int SapId;
  int RollNo;
  int Phone;
  int Year;
  float SGPA[8];
  char name[100];
  char EmailId[100];
};

// Global Variable Declaration

int RecordCount = 0;
struct StudentInfo studentrecords[100];

// Functions Initialisation

void addStudent();

// Main function

int main() {
  printf("Welcome to Student Record and Result Management System\n");
  addStudent();
}

// Function Defination

void addStudent() {
  if (RecordCount == 100) {
    printf("Database is full\n");
    return;
  }
  printf("Enter Name of the Student: ");
  scanf("%99[^\n]", studentrecords[RecordCount].name);
  printf("Enter your Sap ID: ");
  do {
    scanf("%d", &studentrecords[RecordCount].SapId);
    if (studentrecords[RecordCount].SapId < 590000000 ||
        studentrecords[RecordCount].SapId > 590099999) {
      printf("The Sap ID is invlaid\nRe-enter your Sap ID: ");
    }
  } while (studentrecords[RecordCount].SapId < 590000000 ||
           studentrecords[RecordCount].SapId > 590099999);
}