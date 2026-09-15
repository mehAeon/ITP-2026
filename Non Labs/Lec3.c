#include <stdio.h>
#include <string.h>

struct S {
    int left;
    int right;
} s1, s2;

typedef struct {
    int leg;
    int arm;
} S2;

int main ()
{
    int Array[3] = {1, 5, 13};
    printf("%d\n", *Array);
    printf("%d\n", *(Array+2));
    printf("%d\n", *(int*)((char*)Array + sizeof(int)*2));
    printf("%d\n", *(1+Array));
    printf("%d\n", 1[Array]);

    struct S lol;
    S2 human;
    double d = 0x555;
    printf("%f\n", d);
    return 0;
}