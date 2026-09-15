#include <stdio.h>

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
    printf("First = %d, Second = %d", a, b);
    return 0 ;
}