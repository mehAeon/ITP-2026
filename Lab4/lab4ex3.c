#include <stdio.h>

typedef union {
    unsigned long long int dvalue;
    char svalue[8];
} Encryptor;

void encryption (Encryptor *e) {
    for (int i=0; i<7; i+=2) {
        char temp = e->svalue[i];
        e->svalue[i] = e->svalue[i+1];
        e->svalue[i+1] = temp;
    }
}

int main () {
    unsigned long long int a;
    Encryptor e1;
    //printf("Enter:\n");
    scanf("%d", &a);

    e1.dvalue = a;
    printf("Original message: %d\n\n", e1.dvalue);

    encryption(&e1);
    printf("Encrypted message: %d\n\n", e1.dvalue);

    encryption(&e1);
    printf("Decrypted message: %d\n\n", e1.dvalue);

    return 0;
}