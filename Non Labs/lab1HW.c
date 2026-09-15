#include <stdio.h>

int main ()
{
    int x = 10, y = 5;
    printf("Printing operations between x = [%d] and y = [%d]\n", x, y);
    printf("- Addition: %d + %d = %d\n", x, y, x + y);
    printf("- Subtraction: %d - %d = %d\n", x, y, x - y);
    printf("- Multiplication: %d * %d = %d\n", x, y, x * y);
    printf("- Division: %d / %d = %d\n", x, y, x / y);
    return 0;
}