#include <stdio.h>
#include <string.h>

/* Exercise 1 */

int main ()
{
    char Str[20];
    printf("Input your string:\n");
    scanf("%19s", Str);

    int len = strlen(Str);

    for (int i = len; i >= 0; i--) {
        printf("%c", Str[i]);
    }
    return 0 ;
}