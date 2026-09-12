#include <stdio.h>

int main() {
    char Str[256]; 
    FILE *file;
    file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("File Error.\n");
        return 1;
    }


    printf("Input your string: ");
    fgets(Str, sizeof(Str), stdin);

    fputs(Str, file);
    fclose(file);

    printf("Check output.txt\n");
    return 0;
}