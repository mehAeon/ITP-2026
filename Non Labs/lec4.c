#include <stdio.h>
#include <string.h>

int main () {
    int x = 4;
    
    switch (x + 1) {
        case 3: printf("1\n"); break;
        case 4: printf("2\n"); break;
        default: printf("done\n");
    }
}