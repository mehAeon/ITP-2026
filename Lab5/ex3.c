#include <stdio.h>

enum weekday {
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
} day1;

char* weekdayConvert (enum weekday *d) {
    switch (*d) {
        case Monday: return "Monday";
        case Tuesday: return "Tuesday";
        case Wednesday: return "Wednesday";
        case Thursday: return "Thursday";
        case Friday: return "Friday";
        case Saturday: return "Saturday";
        case Sunday: return "Sunday";
        default: return "";
    }
}

int main () {
    scanf("%d", &day1);

    printf("%s", weekdayConvert(&day1));

    return 0;
}