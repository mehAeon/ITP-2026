#include <stdio.h>

struct Birthday {
    unsigned short day : 5;
    unsigned short month : 4;
    unsigned short year : 7;
};

int main () {
    struct Birthday b1;
    b1.day = 18;
    b1.month = 7;
    b1.year = 2008 - 1900;
    printf("%d %d %d\n%d", b1.day, b1.month, b1.year + 1900, sizeof(b1));
    return 0;
}