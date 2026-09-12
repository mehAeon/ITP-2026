#include <stdio.h>
#include <stdlib.h>

/* Exercise 3 */

void pyramid (int n) {
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

void right_pyramid (int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 1 + i; j++) {
            printf("*");
        }
        for (int j = 0; j < n - 1 - i; j++) {
            printf(" ");
        }
        printf("\n");
    }
}

void left_pyramid (int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            printf(" ");
        }
        for (int j = 0; j < 1 + i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void pillar (int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void spike (int n) {
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < 1 + i; j++) {
            printf("*");
        }
        for (int j = 0; j < n - 1 - i; j++) {
            printf(" ");
        }
        printf("\n");
    }
    for (int i = n / 2; i < n; i++) {
        for (int j = n - i; j > 0; j--) {
            printf("*");
        }
        for (int j = 0; j < i - n / 2; j++) {
            printf(" ");
        }
        printf("\n");
    }
}

/* argv[1] = n, argv[2] = figure*/
int main (int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int fig = atoi(argv[2]);

    if (fig == 0) {
        printf("\nPyramid:\n");
        pyramid(n);
    }

    else if (fig == 1) {
        printf("\nLeft Pyramid:\n");
        left_pyramid(n);
    }

    else if (fig == 2) {
        printf("\nRight Pyramid:\n");
        right_pyramid(n);
    }

    else if (fig == 3) {
        printf("\nSpike:\n");
        spike(n);
    }

    else {
        printf("\nPillar:\n");
        pillar(n);
    }
}