#include <stdio.h>
#include <stdlib.h>

/* Exercise 2 */

int main (int argc, char *argv[])
{
    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            printf(" ");
        }
        for (int j = 0; j < 1 + i * 2; j++) {
            printf("*");
        }
        for (int j = 0; j < n - 1 - i; j++) {
            printf(" ");
        }
        printf("\n");
    }
}