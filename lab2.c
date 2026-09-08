#include <stdio.h>

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

/* Exercise 4 */
void swap (int* x, int* y)
{
    int ty = *y;
    int t = *x;
    *x = ty;
    *y = t;
}

int main ()
{
    int a, b;
    printf("Input the first parameter:\n");
    scanf("%d", &a);
    printf("Input the second parameter:\n");
    scanf("%d", &b);

    swap(&a, &b);
    printf("A = %d, B = %d", a, b);
    return 0 ;
}