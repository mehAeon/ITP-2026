#include <stdio.h>
#include <string.h>

typedef struct {
    short day;
    char month[15];
    int year;
} exam_day;

typedef struct {
    char name[20];
    char surname[20];
    short group_number;
    exam_day examday;
} student;

student s1;
exam_day day1;
char fname[20], fsurname[20], fmonth[15];
int fyear;
short fday, fgroup_number;

void assignStudentInfo () {
    day1.year = fyear;
    strcpy(day1.month, fmonth);
    day1.day = fday;

    strcpy(s1.name, fname);
    strcpy(s1.surname, fsurname);
    s1.group_number = fgroup_number;
    s1.examday = day1;
}

void printStudentInfo (student* s) {
    printf("------------- FAKE HARVARD STUDENT CARD -------------\n\n");
    printf("NAME: %s\n", s1.name);
    printf("SURNAME: %s\n", s1.surname);
    printf("GROUP NUMBER: %hd\n\n", s1.group_number);
    printf("EXAM YEAR: %d\n", s1.examday.year);
    printf("EXAM MONTH: %s\n", s1.examday.month);
    printf("EXAM DAY: %hd\n", s1.examday.day);
}

int main () {
    printf("You have to create a fake student to sneak into a Harvard exam.\n'Name Surname GroupNumber Year Month Day\n");
    scanf("%s %s %hd %d %s %hd", fname, fsurname, &fgroup_number, &fyear, fmonth, &fday);

    assignStudentInfo();

    student* p = &s1;
    printStudentInfo(p);

    return 0;
}