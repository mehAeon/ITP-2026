#include <stdio.h>
#define N 5

int main() {
/* an array with 5 elements */
double balance[N] = {1000.0, 2.0, 3.4, 17.0, 50.0};
double *p;
int i;
p = balance;
/* output each array element's value */
printf("Array values using pointer\n");
for (i = 0; i < N; i++) {
printf("*(p + %d) : %f\n", i, p[i]); /* p[i] == *(p + i) */
}
printf("Array values using balance as address\n");
for (i = 0; i < N; i++) {
printf("*(balance + %d) : %f\n", i, balance[i]); /* balance[i] = *(balance + i) */
}
return 0;
}

int bmain ()
{
    char greeting1[6] = {'H','e','l','l','o','\0',};
    char greeting[] = "Hello";
    printf("Yo, %s\n", greeting);

    /* type arrayName[arraySize]; */
    int lol[5] = {1, 2, 3, 4, 5}; /* FIXED-SIZE. CANNOT GO OVER 5 ELEMENTS*/
    /* TAKES AROUND 20 BYTES (INT = 4 BYTES)*/

    double balance[] = {1000.0, 2.0, 3.4, 7.0, 50.0}; /* IMPLICITLY */
    balance[4] = 12.0; /* CHANGING THE VALUE IN INDEX 4*/

    /* pass pointer to the array as an argument. If arr is changed in the function, balance[5] will also change */
    /* avg = getAverage(balance, 5); */


    return 0;
}